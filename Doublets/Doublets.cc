/*
Cristina S. Alonso
Assignment 5
BFS algorithm working.
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
  string name;
  vector<Edge> adj;
  int dist;
  Vertex *parent;

  Vertex( const string & nm ) : name( nm )
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
    void printPath( const string & t_word ) const;
    void search( const string & startName );

  private:
    typedef map<string,Vertex *> vmap;
    vmap levels;

    Vertex * getVertex( const string & v_word );
    void printPath( const Vertex & vt ) const;
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

// Adjacency list
void Doublets::addEdge( const string & s_word, const string & t_word )
{
  Vertex * v = getVertex( s_word );
  Vertex * w = getVertex( t_word );
  v->adj.push_back( Edge( w ) );
}

// Transform word to vertex
void Doublets::printPath( const string & t_word ) const
{
  auto itr = levels.find( t_word );
  const Vertex & w = *(*itr).second;
  printPath( w );
  cout << "\n\n";
  printLevels( w );

}

// Fixes any duplicates
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

// Recursive print
void Doublets::printPath( const Vertex & vt ) const
{
  if( vt.parent != nullptr )
  {
    printPath( *vt.parent );
    cout << " --> [" << vt.dist << "]: ";
  }
  cout << vt.name;
}

// Finds edge distances in map
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

void Doublets::search( const string & startName )
{
  auto itr = levels.find( startName );

  Vertex *start = (*itr).second;
  list<Vertex *> q;
  q.push_back( start );
  start->dist = 0;

  while( !q.empty( ) )
  {
    Vertex *v = q.front( );
    q.pop_front( );
    for( int i = 0; i < v->adj.size( ); i++ )
    {
      Edge e = v->adj[ i ];
      Vertex *w = e.vt;

      if( w->dist == INFINITY )
      {
          w->dist = v->dist + 1;
          w->parent = v;
          q.push_back( w );
      }
    }
  }
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

  for(auto i : active_list)
  {
    for( auto j : active_list)
    {
      if(isadjacent(i, j))
        d.addEdge( i, j );
    }
  }
  d.search( initial );
  d.printPath( final );
  return 0;
}

#endif
