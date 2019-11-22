#include "Sort.h"
#include <iostream>
#include <string>

// TrieSort implementation

class Sort::ImplSort
{

private:

  struct Node
  {
    bool has_data;
    std::string data;
    Node *children[26] = {};

    Node( ) : has_data(false), data("")
    {
    }

    ~Node()
    {
      delete [] *children;
    }

    void insert(const std::string & key, const std::string & value)
    {
      const char *k = &key[0u]; // cool trick to iterate through key

      if( !*k ) // if the string is empty, then done
      {
        return;
      }
      int index = *k - 'A'; // convert to int between 1 - 26
      if(!children[index]) // if null, create another trie node
        children[index] = new Node();

      children[index]->insert(k + 1, value); // and recursively insert

      if( key.length() == 1 ) // now going backwards
      {
        // insert value at the end of the key (leaf)
        data = std::move(value);
        has_data = true;
      }

    }

    void enumerate(std::ostream& output_file)
    {
      int i; // for loop to iterate through children
      for( i = 0; i < 26; i++)
      {
        if(children[i])
        {
          if(has_data)
          {
            output_file << data << "\n";
          }
          children[i]->enumerate(output_file);
        }
      }
    }

  };

  Node *root = nullptr;

public:

  void insert(const std::string & key, const std::string & value)
  {
    if(root == nullptr)
    {
      root = new Node();
    }
    // specify key length to be 10
    root->insert(key.substr(0,10),value);
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
