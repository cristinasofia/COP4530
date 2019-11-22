/*
Cristina S. Alonso
Assignment 6
Attempt at bidirectional BFS algorithm.
*/

#ifndef Doublets_H
#define Doublets_H

#include <fstream>
#include <iostream>
#include <sstream>

#include <map>
#include <vector>
#include <string>
#include <list>
using namespace std;

using std::string;
using std::vector;
using std::list;
using std::map;

static const int INFINITY = INT_MAX;
struct Vertex;

struct Edge
{
  Vertex *vt;
  Edge( Vertex *d = 0 )
    : vt( d ) { }
};

struct Vertex
{
  string word;
  vector<Edge> adj;
  int dist;
  Vertex *parent;

  Vertex( const string & nm ) : word( nm )
    { reset( ); }

  void reset( )
    { dist = INFINITY; parent = NULL; }
};

class Doublets
{
public:
  Doublets( ) { }
  ~Doublets( );
  void addEdge( const string & s_word, const string & t_word );
  void printBiPath( const string & s_word, const string & t_word ) const;
  void bidirectional( const string & s_word, const string & t_word );

private:
  using vmap = map<string,Vertex *>;
  vmap levels;
  Vertex * getVertex( const string & v_word );
  void printForward( const Vertex & vt ) const;
  void printReverse( const Vertex & vt ) const;
  void printLevels( const Vertex & vt ) const;
};

bool isadjacent( string & a, string & b)
{
  int count = 0; // store count of differences

  // iterate through all characters
  for(int i = 0; i < a.length(); i++)
  {
    if(a[i] != b[i]) count++;
    if( count > 1 ) return false;
  }
  return count == 1 ? true : false;
}

void Doublets::addEdge( const string & s_word, const string & t_word )
{
    Vertex * v = getVertex( s_word );
    Vertex * w = getVertex( t_word );
    v->adj.push_back( Edge( w ) );
}

void Doublets::printBiPath( const string & s_word, const string & t_word ) const
{
  auto itr = levels.find( s_word );
  auto itr2 = levels.find( t_word );

  const Vertex & w = *(*itr).second;
  const Vertex & u = *(*itr2).second;

  printForward( u );
  cout << "\n";
  printLevels( u );
  cout << "\n\n";
  printReverse( w );
  cout << "\n";
  printLevels( u );
  cout << "\n\n";

}

// Fixes duplicates
Vertex * Doublets::getVertex( const string & v_word )
{
  auto itr = levels.find( v_word );
  if( itr == levels.end( ) )
  {
    Vertex *n = new Vertex( v_word );
    levels[ v_word ] = n;
    return n;
  }
  return (*itr).second;
}


void Doublets::printForward( const Vertex & vt ) const
{
    if( vt.parent != nullptr )
    {
        printForward( *vt.parent );
        cout << " --> [" << vt.dist << "]: ";
    }
    cout << vt.word;
}

void Doublets::printReverse( const Vertex & vt ) const
{
  cout << vt.word;
  if( vt.parent != nullptr )
  {
    cout << " --> [" << vt.dist << "]: ";
    printReverse( *vt.parent );
  }
}

void Doublets::printLevels( const Vertex & vt ) const
{
  if( vt.parent != nullptr )
  {
    printLevels( *vt.parent );
    cout << " ... level " << vt.dist << " has ";
    int count = 0;
    for(auto it : levels)
    {
      if( it.second->dist == vt.dist )
      {
        count++;
      }
    }
    cout << count << " elements\n";
  }
}

Doublets::~Doublets( )
{
  for( auto it : levels )
    delete it.second;
}

void Doublets::bidirectional( const string & s_word, const string & t_word )
{

  auto itr1 = levels.find( s_word );
  auto itr2 = levels.find( t_word );

  Vertex *start = (*itr1).second;
  Vertex *target = (*itr2).second;

  list<Vertex *> s;
  list<Vertex *> t;

  vector<Vertex *> s_path;
  vector<Vertex *> t_path;

  start->dist = 0;
  target->dist = 0;

  s.push_back( start );
  t.push_back( target );

  map<string,bool> s_found;
  map<string,bool> t_found;
  for( auto it = levels.begin(); it != levels.end(); it++ )
  {
    s_found[it->second->word] = false;
    t_found[it->second->word] = false;
  }
  s_found[start->word] = true;
  t_found[target->word] = true;

  while( !s.empty() && !t.empty() )
  {
    if( !s.empty() )
    {
      Vertex * v = s.front( );
      s.pop_front( );

      for( int i = 0; i < v->adj.size( ); i++ )
      {
        Edge e = v->adj[ i ];
        Vertex * w = e.vt;

        if( t_found[ w->word ] )
        {
          s_path.push_back( w );
        }
        else if( w->dist == INFINITY )
        {
          w->dist = v->dist + 1;
          w->parent = v;
          s.push_back( w );
          s_found[ w->word ] = w;
        }
      }
    }
    if( !t.empty() )
    {
      Vertex * u = t.front();
      t.pop_front();

      for( int i = 0; i < u->adj.size(); i++ )
      {
        Edge e = u->adj[ i ];
        Vertex * w = e.vt;

        if( s_found[ w->word ] )
        {
          t_path.push_back( w );
        }
        else if( w->dist == INFINITY )
        {
          w->dist = u->dist + 1;
          w->parent = u;
          t.push_back( w );
          t_found[ w->word ] = w;
        }
      }
    }
  }

  printBiPath(s_path[0]->word, t_path[0]->word);
}

int main( int argc, char *argv[ ] )
{
  Doublets d;
  string initial = argv[2];
  string final = argv[3];

  // Reading file
  ifstream inFile( argv[ 1 ] );
  vector<string> active_list;

  string input;
  while( !getline( inFile, input ).eof() )
  {
    string str;
    istringstream iss( input );
    iss >> str;
    if(initial.length() == str.length())
    {
      active_list.push_back(str);
    }
  }

  // Hamming distance = 1
  for( auto i : active_list )
  {
    for(auto j : active_list)
    {
      if(isadjacent(i, j))
      {
        d.addEdge( i, j );
      }
    }
  }

  d.bidirectional(initial, final);

  return 0;
}

#endif
