#ifndef CHAR_VECTOR_WRAPPER
#define CHAR_VECTOR_WRAPPER

//Includes
#include <iostream>
#include <vector>
#include <map>
#include <algorithm>

#include "String.h"

//Declarations
class CharVector {
private:
  std::vector<char> resizeable_array;

  static unsigned int max_print;

public:
  CharVector() :
    resizeable_array{} {
  }

  CharVector(const std::initializer_list<char> &il) :
    resizeable_array{il} {
  }

  ~CharVector() {
    this->Clear();
  }

  char& operator[](const unsigned int index);
  const char& operator[](const unsigned int index) const;
  friend std::ostream& operator<< (std::ostream &out, const CharVector &vector); //for printing
  friend bool operator== (const CharVector &vector_A, const CharVector &vector_B); //for map, for composite key
  friend bool operator< (const CharVector &vector_A, const CharVector &vector_B); //for map
  std::vector<char>::iterator begin();
  std::vector<char>::iterator end();

  const std::vector<char>& GetVector() const;

  void Append(const char &character);
  void Append(const String &string);

  void Transform(std::map<char, char> &map);
  void Reverse();

  unsigned int Length() const;

  void Shrink();
  void Clear();
};

#endif // VECTOR_WRAPPER_TEMPLATE

