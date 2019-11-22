
#include "Sort.h"
#include <iostream>
#include <string>

// BST implementation

class Sort::ImplSort
{

private:
  struct Node
  {
    Node *left;
    Node *right;
    std::string data;

    Node(std::string Data, Node *left = nullptr, Node *right = nullptr)
    {
      data = Data;
      left = nullptr;
      right = nullptr;
    }

    ~Node()
    {
      delete left;
      delete right;
    }

    void insert(const std::string & key, const std::string & value)
    {
      if(value < this->data)
	{
	  if(left)
	    {
	      left->insert(key,value);
	    }
	  else
	    {
	      left = new Node(std::move(value),nullptr,nullptr);
	    }
	}
      else
	{
	  if(right)
	    {
	      right->insert(key,value);
	    }
	  else
	    {
	      right = new Node(std::move(value),nullptr,nullptr);
	    }
	}
    }

    void enumerate(std::ostream& output_file)
    {
      if(left)
	left->enumerate(output_file);
      output_file << data << "\n";
      if(right)
	right->enumerate(output_file);
    }
  };

  Node *root = nullptr;

public:
  void insert(const std::string & key, const std::string & value)
  {
    if(root == nullptr)
      {
	root = new Node(value,nullptr,nullptr);
      }
    else
      root->insert(key,value);
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
