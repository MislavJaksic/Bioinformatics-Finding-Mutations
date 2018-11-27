#ifndef VECTOR_WRAPPER_TEMPLATE
#define VECTOR_WRAPPER_TEMPLATE

//Includes
#include "standard_include.h"
#include "string_wrapper.h"

//Declarations
class VectorWrapper {
private:
  std::vector<char> vector;

public:
  VectorWrapper(std::vector<char> vector) :
    vector(vector) {
  }



  void AppendString(StringWrapper &string) {
    for (unsigned int i = 0; i < string.Length(); i++) {
      char character = string.GetChar(i);
      this->vector.push_back(character);
    }
  }



  unsigned int Length() {
    return this->vector.size();
  }



  void Print() {
    for (auto& element : this->vector) {
      std::cout << element;
    }
    std::cout << std::endl;
  }
};
/*template <class V>
class VectorWrapper {
private:
  std::vector<V> vector;

public:
  VectorWrapper(std::vector<V> vector) :
    vector(vector) {
  }



  void AppendString(StringWrapper &string) {
    for (unsigned int i = 0; i < string.Length(); i++) {
      char character = string.GetChar(i);
      this->vector.push_back(character);
    }
  }



  unsigned int Length() {
    return this->vector.size();
  }



  void Print() {
    for (auto& element : this->vector) {
      std::cout << element;
    }
  }
};*/

#endif // VECTOR_WRAPPER_TEMPLATE
