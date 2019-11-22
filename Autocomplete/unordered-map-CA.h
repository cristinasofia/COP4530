#ifndef UNORDERED_MAP_CA_H
#define UNORDERED_MAP_CA_H

#include <string>
#include <vector>
using std::vector;
using std::string;
using std::size_t;

// FNV1a Hash Function
// Rehashing works with 32 bit prime and offset basis, but
// gets weird for the 64-bit. If any issues, please uncomment
// the 32 bit and comment out the 64 bit numbers.
class fnv_1a
{
public:
  size_t operator()(string const & x) const
  {
    uint64_t hash = 0xcbf29ce484222325; // FNV offset basis for 64 bit
    //size_t hash = 2166136261u; // FNV offset basis for 32 bit
    for(string::const_iterator it = x.begin(), end = x.end();
            it != end; ++it)
    {
      hash ^= *it;
      hash *= 1099511628211u; // FNV prime for 64 bit
      //hash *= 16777619u; // FNV prime for 32 bit
    }
    return hash;
  }
};

template <typename Object>
class equal_to
{
  public:
    bool operator() ( const Object & lhs, const Object & rhs ) const
      { return lhs == rhs; }
};

// method in the book for rehashing tables
bool isPrime( size_t n );
size_t nextPrime( size_t n );
enum EntryType { EMPTY, DELETED, ACTIVE };

template <typename KeyType, typename T, typename HashType = fnv_1a, typename EqualType = std::equal_to<KeyType> >
class unordered_map_CA
{
private:
	using MapType = unordered_map_CA<KeyType, T, HashType, EqualType>;
	using ValueType = std::pair<KeyType, T>;
  using VectorType = std::vector<ValueType>;
  using iterator = typename VectorType::iterator;
  using const_iterator = typename VectorType::const_iterator;

  VectorType hashObj; // buckets of pairs
  std::vector<EntryType> entries; // information on bucket status

  HashType myhash; // hash function
  EqualType eq; // equal to pred for keys
  size_t buckets; // size of vectors
  size_t occupied; // number of elements that are not empty

  bool isActive( size_t index ) const
  {
    return entries[index] == ACTIVE;
  }

  // linear probing method
  size_t findPos( const KeyType & x ) const
  {
    size_t offset = 0;
    size_t index = myhash( x ) % hashObj.size( );

    while( entries[index] != EMPTY &&
           !eq(hashObj[index].first, x) )
    {
      index += offset;  // Compute ith probe
      offset++;
      if( index >= hashObj.size( ) )
        index -= hashObj.size( );
    }
    return index;
  }

  void rehash()
  {
    // load factor
    double factor = double(occupied)/double(buckets);
    // for linear probing, performance degrades
    // when the load factor grows beyond 0.7
    if( factor < 0.7 ) return;
    // else rehash
    std::vector<ValueType> oldHashObj = hashObj;
    std::vector<EntryType> oldEntries = entries;
    size_t oldBuckets = buckets;

    // create new double-sized, empty table
    buckets = nextPrime( 2 * oldBuckets );
    entries.resize( buckets );
    clearAll();

    // copy table over
    hashObj.resize( buckets );
    for( size_t i = 0; i < oldBuckets; i++ )
    {
      if( oldEntries[i] == ACTIVE )
      {
        hashObj[i] = oldHashObj[i];
        entries[i] = ACTIVE;
        occupied++;
      }
    }
  }
public:
	unordered_map_CA(): buckets( nextPrime(1001) ), occupied( 0 )
	{
    hashObj.resize(buckets);
    entries.resize(buckets);
    clearAll();
	}
  // initiate vector of entries
  void clearAll( )
  {
    occupied = 0;
    for( auto e : entries )
      e = EMPTY;
  }
  iterator begin( )
  {
    return hashObj.begin();
  }
  const_iterator begin( ) const
  {
    return hashObj.begin();
  }
  iterator end( )
  {
    return hashObj.end();
  }
  const_iterator end( ) const
  {
    return hashObj.end();
  }
	size_t size() const
	{
		return occupied;
	}
	bool empty() const
	{
		return occupied == 0;
	}
  // returns iterator of vector of hashObjs
  iterator find(const KeyType & key)
	{
    auto bucket = findPos(key);
    if( isActive(bucket) )
      return begin() + bucket;
    else
      return end();
	}
  const_iterator find(const KeyType & key) const
  {
    auto bucket = findPos(key);
    if( isActive(bucket) )
      return begin() + bucket;
    else
      return end();
  }
  // looks for key, and if bucket is available then insert
  T & operator[]( const KeyType & key )
  {
    rehash();
    auto bucket = findPos( key );
    if( entries[bucket] != ACTIVE )
    {
      entries[bucket] = ACTIVE;
      hashObj[bucket] = ValueType(key,T());
      occupied++;
    }
    return hashObj[bucket].second;
  }
};

// test if number is prime
bool isPrime( size_t n )
{
  if( n == 2 || n == 3 )
    return true;
  if( n == 1 || n % 2 == 0 )
    return false;
  for( int i = 3; i * i <= n; i += 2 )
    if( n % i == 0 )
      return false;
  return true;
}

// return prime number >= size of n
size_t nextPrime( size_t n )
{
  if( n % 2 == 0 )
      n++;
  for( ; !isPrime( n ); n += 2 )
      ;
  return n;
}

#endif
