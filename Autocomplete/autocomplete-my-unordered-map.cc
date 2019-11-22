#include <iostream>	// for cin, cout
#include <fstream> // for ifstrean, ofstream
#include <sstream> // for istringstream

//#include <unordered_map>
#include "unordered-map-CA.h"
#include "List-CA.h"
#include <string>

using std::cout;
using std::string;

// attempt to make program less verbose
using termPair = std::pair<long, string >; // for each (occurrence,word) pair
using termList = List_CA< termPair >; // list of termPairs

// return true if prefix is a prefix of word
bool isPrefix( const string & prefix, const string & word )
{
  if(word.compare(0, prefix.length(), prefix) == 0)
    return true;
  return false;
}

// return number of characters without spaces
int numChar( const string & str)
{
  int count = 0;
  for(auto &s : str)
  {
    if(!isspace(s) && s != ',')
      count++;
  }
  return count;
}

// overloaded operator prints list of term pairs
std::ostream & operator<<( std::ostream & out, const termList & list )
{
  int count = 1;
  for(auto l : list)
  {
    out << "\t" << count << " " << l.second;
    out << " (" << l.first << " instances)\n";
    count++;
  }
  out << "\n";

  return out;
}

// prints values in map at key found by map iterator
template <class ForwardIterator, class T>
void printValues( const ForwardIterator & f, const T & t )
{
    if( f == t.end( ) )
        return;

    cout << f->second;
}

// printing all keys and values in map
template <class Map>
void printAll( const Map & m )
{
    cout << "Map contains " << m.size( ) << " search terms.\n";
    for( auto &index : m )
    {
      cout << "search term = " << index.first << "\n";
      cout << index.second;
    }
}

int main(int argc, char *argv[])
{
  // read in the terms from a file
  string fileName = argv[1]; // source file
  int maxMatch = std::stoi(argv[2]); // maximum number of matches to return
  int maxChar = std::stoi(argv[3]); // maximum number of characters that can appear in an autocomplete request

  std::ifstream in(fileName); // intialize file input

  termList thePairs; // list of pairs from file input

  string line;
  while(std::getline(in, line))
  {
    long weight;
    string query;

    std::istringstream iss(line);
    iss >> weight;
    iss.get();  // ignores space inbetween
    std::getline(iss,query);

    thePairs.push_back(std::make_pair(weight,query));
  }

  // at each map index there is a list of (occurrence, word) pairs
  //std::unordered_map< string, termList > st;
  unordered_map_CA< string, termList> st;

  // read in queries from standard input and print out the top
  // maxMatch matching terms with a limit of maxChar characters
  cout << "Ask me which is most popular!" << "\n";
  while(std::cin)
  {
    string theKey;
    std::getline(std::cin,theKey);
    if(theKey.empty()) continue; // does not accept empty string
    cout << "Top answers for '" << theKey << "'\n";

    string key; // string of theKey prefixes
    for(char k : theKey)
    {
      key += k;

      if(st.find(key) == st.end()) // key not found, find in list of pairs and add
      {
        termList &terms = st[key];
        for(auto &p : thePairs) // iterate through pairs
        {
          // if query in pair is prefix
          if(isPrefix(key,p.second))
          {
            terms.push_back(p); // pair to append
          }
          if(terms.size() >= maxMatch) break; // list has max number of matches
        }
      }
      if(numChar(key) == maxChar) break; // max number of characters
    }

    printValues(st.find(key),st);
    //printAll(st);

    cout << "Ask me for another autocomplete." << "\n";
  }

   return 0;
}
