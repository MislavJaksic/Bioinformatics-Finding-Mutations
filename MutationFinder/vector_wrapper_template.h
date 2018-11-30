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
  VectorWrapper(std::vector<char> &vector) :
    vector(vector) {
  }



  void Append(char &character) {
    this->vector.push_back(character);
  }

  void Append(StringWrapper &string) {
    char character;
    for (unsigned int i = 0; i < string.Length(); i++) {
      character = string.GetChar(i);
      this->Append(character);
    }
  }



  void Transform(MapWrapper<char, char> &map) {
    char character;
    for (unsigned int i = 0; i < this->Length(); i++) {
      character = this->vector[i];
      if (map.IsExists(character)) {
        this->vector[i] = map.Get(character);
      }

    }
  }

  MapWrapper<char, int> CountValues() {
    std::map<char, int> init_map;
    MapWrapper<char, int> occurrences{init_map};

    char character;
    int count_plus_one;
    int one;
    for (unsigned int i = 0; i < this->Length(); i++) {
      character = this->vector[i];
      if (occurrences.IsExists(character)) {
        count_plus_one = occurrences.Get(character) + 1;
        occurrences.Set(character, count_plus_one);
      } else {
        one = 1;
        occurrences.Set(character, one);
      }
    }

    return occurrences;
  }



  char& operator[](const unsigned int &i) {
    return this->vector[i];
  }

  bool IsOneGreaterThenTwoOfLength(unsigned int one, unsigned int two, unsigned int length) {
    char char_one;
    char char_two;
    for (unsigned int i = 0; i < length; i++) {
      char_one = this->vector[one + i];
      char_two = this->vector[two + i];
      if (char_one > char_two) {
        return true;
      } else if (char_one < char_two) {
        return false;
      }
    }
    return false;
  }

  unsigned int Length() {
    return this->vector.size();
  }




  void Print() {
    for (auto& element : this->vector) {
      std::cout << element;
    }
  }

  void PrintFromTo(unsigned int start, unsigned int stop) {
    for (unsigned int i = start; i < stop; i++) {
      std::cout << this->vector[i];
    }
    std::cout << std::endl;
  }



  void Shrink() {
    this->vector.shrink_to_fit();
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
