#include "Sort.h"
#include <iostream>
#include <string>

// HeapSort implementation

class Sort::ImplSort
{

private:

  struct Node
  {
    Node *left;
    Node *right;
    std::string data;
    int l; // counts left nodes
    int r; // counts right nodes

    Node(std::string Data, Node *lptr = nullptr, Node *rptr = nullptr,
      int lcount = 0, int rcount = 0)
    {
      data = Data;
      left = lptr;
      right = rptr;
      l = lcount;
      r = rcount;
    }

    ~Node()
    {
      delete left;
      delete right;
    }

    void insert(const std::string & key, const std::string & value)
    {
      std::string val = std::move(key);

      if(val < this->data)
      {
        val.swap(data); // swap to determine what stays at root
      }
      if( l < r ) // insert into subtree, while counts keep balance
      {
        l++;
        if(left)
        {
          left->insert(val,val); // in this assignment, key = value
        }
        else
        {
          left = new Node(std::move(val),nullptr,nullptr);
        }
      }
      else
      {
        r++;
        if(right)
        {
          right->insert(val,val);
        }
  	    else
  	    {
  	      right = new Node(std::move(val),nullptr,nullptr);
  	    }
	    }
    }

    std::string remove() // a.k.a. deleteMin, which preserves heap property
    {
      std::string remember = data;

      if( (l > 0) && (r > 0) )
      {
        if( left->data < right->data ) // find a new "min" candidate
        {
          l--;
          data = left->remove(); // decrease the left count for all nodes
          if(l == 0) // until reaching the end of subtree
          {
            delete left;
            left = nullptr;
          }
        }
        else // maybe new candidate is on the right
        {
          r--;
          data = right->remove();
          if(r == 0)
          {
            delete right;
            right = nullptr;
          }
        }
      }
      else if( l > 0 ) // if the left subtree isn't decomposed
      {
        l--;
        data = left->remove();
        if(l == 0)
        {
          delete left;
          left = nullptr;
        }
      }
      else if( r > 0 ) // and if the right subtree isn't decomposed
      {
        r--;
        data = right->remove();
        if(r == 0)
        {
          delete right;
          right = nullptr;
        }
      }

      return remember;
    }

    void enumerate(std::ostream& output_file)
    {
      while( l || r ) // keep "popping" the min from the root (evenly)
      {
          output_file << remove() << "\n"; // one leaf
          output_file << remove() << "\n"; // two leaf
      }
    }

  };

  Node *root = nullptr;

public:

  void insert(const std::string & key, const std::string & value)
  {
    if(root == nullptr)
    {
      root = new Node(std::move(value),nullptr,nullptr);
    }
    else
    {
      root->insert(key,value);
    }

  }
  void enumerate(std::ostream& output_file)
  {
    root->enumerate(output_file);
  }

};


Sort::Sort() : implSort_(new ImplSort) {}

Sort::~Sort()
{
  delete implSort_;
}

void Sort::insert(const std::string & key, const std::string & value)
{
  implSort_->insert(key,value);
}

void Sort::enumerate(std::ostream& output_file)
{
  implSort_->enumerate(output_file);
}
