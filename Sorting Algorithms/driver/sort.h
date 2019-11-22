/* Using pImpl idiom */

#include <ostream>
#include <string>
#include <memory>

class Sort
{

public:
  Sort();
  ~Sort();

  void insert(const std::string & key, const std::string & value);
  void enumerate(std::ostream& output_file);

private:

  class ImplSort;         // Forward declaration of the implementation class
  ImplSort *implSort_;    // pImpl

};
