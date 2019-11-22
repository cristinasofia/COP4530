#include "Sort.h"
#include <iostream>
#include <string>

int main()
{
  Sort s;

  std::string s_in;
  while(std::getline(std::cin,s_in))
    {
      s.insert(s_in,s_in);
    }
  s.enumerate(std::cout);
}
