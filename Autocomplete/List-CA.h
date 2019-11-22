#ifndef LIST_CA_H
#define LIST_CA_H

/*
Implementation of list class.
The following was changed: head and tail pointers, init( ),
push_back( const T & x), push_back ( T && x ), and pop_front( ).
*/

template< typename T >
class List_CA
{
private:
  struct Node
  {
    T data;
    Node *prev;
    Node *next;

    Node( const T & d = T(), Node * p = nullptr, Node * n = nullptr )
    : data( d ), next( n )
    {
    }
    Node( T && d, Node * p = nullptr, Node * n = nullptr )
    : data( std::move( d ) ), next( n )
    {
    }
  };

public:
  class const_iterator
  {
  public:
    const_iterator( ) : current( nullptr )
    {
    }
    const T & operator* ( ) const
    {
      return retrieve( );
    }
    const_iterator & operator++ ( )
    {
      if( current )
        current = current->next;
      return *this;
    }
    const_iterator operator++ ( int )
    {
      const_iterator old = *this;
      ++( *this );
      return old;
    }
    const_iterator & operator-- ( )
    {
      if( current )
        current = current->prev;
      return *this;
    }
    const_iterator operator-- ( int )
    {
      const_iterator old = *this;
      --( *this );
      return old;
    }
    bool operator== ( const const_iterator & rhs ) const
    {
      return current == rhs.current;
    }
    bool operator!= ( const const_iterator & rhs ) const
    {
      return !( *this == rhs );
    }
  protected:
    Node *current;
    T & retrieve( ) const
    {
      return current->data;
    }
    const_iterator( Node *p ) : current( p )
    {
    }
    friend class List_CA<T>;
  };

  class iterator : public const_iterator
  {
  public:
    iterator( )
    {
    }
    T & operator* ( )
    {
      return const_iterator::retrieve( );
    }
    const T & operator* ( ) const
    {
      return const_iterator::operator*( );
    }
    iterator & operator++ ( )
    {
      if( this->current )
        this->current = this->current->next;
      return *this;
    }
    iterator operator++ ( int )
    {
      iterator old = *this;
      ++( *this );
      return old;
    }
    iterator & operator-- ( )
    {
      if( this->current )
        this->current = this->current->prev;
      return *this;
    }
    iterator operator-- ( int )
    {
      iterator old = *this;
      --( *this );
      return old;
    }
  protected:
    iterator( Node *p ) : const_iterator( p )
    {
    }
    friend class List_CA<T>;
   };

  public:
  List_CA( )
  {
    init( );
  }
  void init( ) // initialize pointers to null
  {
    theSize = 0;
    first = nullptr;
    last = nullptr;
  }
  List_CA( const List_CA & rhs )
  {
    init( );
    for( auto & x : rhs )
      push_back( x );
  }
  ~List_CA( )
  {
    clear( );
    delete first;
    delete last;
  }
  List_CA & operator= ( const List_CA & rhs )
  {
    List_CA copy = rhs;
    std::swap(*this, copy);
    return *this;
  }
  List_CA( List_CA && rhs )
  : theSize(rhs.theSize),first(rhs.first),last(rhs.last)
  {
    rhs.theSize = 0;
    rhs.first = nullptr;
    rhs.last = nullptr;
  }
  List_CA & operator=( List_CA && rhs )
  {
    std::swap(theSize, rhs.theSize);
    std::swap(first,rhs.first);
    std::swap(last,rhs.last);
    return *this;
  }
  iterator begin( )
  {
    return iterator( first );
  }
  const_iterator begin( ) const
  {
    return const_iterator( first );
  }
  iterator end( )
  {
    return iterator( nullptr );
  }
  const_iterator end( ) const
  {
    return const_iterator( nullptr );
  }
  int size( ) const
  {
    return theSize;
  }
  bool empty( ) const
  {
    return size( ) == 0;
  }
  void push_back( const T & x )
  {
    Node *n = new Node( x ); // new node
    Node *p = last; // last node
    n->prev = p; // insert n after p
    if( p ) // if p != null
    {
      n->next = p->next; // put p->prev in front of n
    }
    else
    {
      n->next = last; // put pointer to last in front
    }
    if ( n->next ) // if after n != null
    {
      n->next->prev = n; // put n behind the node
    }
    else
    {
      last = n; // make n the last node
    }
    if ( n->prev ) // if before n != null
    {
      n->prev->next = n; // put n in front of the node
    }
    else
    {
      first = n; // make n the first node
    }
    theSize++; // increase size
  }
  void push_back( T && x )
  {
    Node *n = new Node( std::move( x ) ); // new node
    Node *p = last; // last node
    n->prev = p; // insert n after p
    if( p ) // if p != null
    {
      n->next = p->next; // put p->prev in front of n
    }
    else
    {
      n->next = last; // put pointer to last in front
    }
    if ( n->next ) // if after n != null
    {
      n->next->prev = n; // put n behind the node
    }
    else
    {
      last = n; // make n the last node
    }
    if ( n->prev ) // if before n != null
    {
      n->prev->next = n; // put n in front of the node
    }
    else
    {
      first = n; // make n the first node
    }
    theSize++; // increase size
  }
  void pop_front( )
  {
    if ( empty() ) // list is empty, cannot delete
      return;
    else
    {
      Node *p = first; // hold temp pointer to delete

      if ( first == last )
        first = last = nullptr; // no nodes remain after removal
      else
      {
        if ( p->prev ) // if the node before itr != nullptr
        {
          p->prev->next = p->next; // attach node before to after itr node
        }
        else
        {
          first = p->next; // if itr->prev = nullptr, then becomes first
        }
        if ( p->next ) // if node after itr != nullptr
        {
          p->next->prev = p->prev; // attach node after to before itr node
        }
        else
        {
          last = p->prev; // if itr->next = nullptr, then becomes last
        }
        delete p; // reclaim memory
      }
      theSize--; // decrease size
    }
  }
  void clear( )
  {
    while ( !empty( ) )
      pop_front( );
  }

  private:
  int theSize; // size of list
  Node *first; // pointer to first node
  Node *last; // pointer to last node

};

#endif
