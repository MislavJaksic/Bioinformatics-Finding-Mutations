#ifndef VECTOR_WRAPPER_TEMPLATE
#define VECTOR_WRAPPER_TEMPLATE

//Includes
#include "standard_include.h"
#include "string_wrapper.h"
#include "map_wrapper_template.h"

//Declarations
class VectorWrapper {
protected:
  std::vector<char> vector;

public:
  VectorWrapper(std::vector<char> vector) :
    vector(vector) {
  }



  void Append(char &character) {
    this->vector.push_back(character);
  }

  void Append(StringWrapper &string) {
    char character;
    for (unsigned int i = 0; i < string.Length(); i++) {
      character = string.GetChar(i);
      this->vector.push_back(character);
    }
  }



  void Transform(MapWrapper<char, char> &map) {
    char character;
    for (unsigned int i = 0; i < this->vector.size(); i++) {
      character = this->vector[i];
      if (map.IsExists(character)) {
        this->vector[i] = map.Get(character);
      }

    }
  }



  char& operator[](const unsigned int &i) {
    return this->vector[i];
  }



  unsigned int Length() {
    return this->vector.size();
  }



  void Print() {
    for (auto& element : this->vector) {
      std::cout << element;
    }
  }
};

bool operator< (VectorWrapper &vector_A, VectorWrapper &vector_B);


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
