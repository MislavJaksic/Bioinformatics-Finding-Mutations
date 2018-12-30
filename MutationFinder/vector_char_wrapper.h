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

  friend bool operator< (const VectorWrapper &vector_A, const VectorWrapper &vector_B) {
    unsigned int length_A = vector_A.vector.size();
    unsigned int length_B = vector_B.vector.size();

    if (length_A < length_B) {
      return true;
    } else if (length_A > length_B) {
      return false;
    }

    for (unsigned int i = 0; i < length_A; i++) {
      if (vector_A.vector[i] > vector_B.vector[i]) {
        return false;
      } else if (vector_A.vector[i] < vector_B.vector[i]) {
        return true;
      }
    }
    return true;
  }

  friend std::ostream& operator<< (std::ostream &out, const VectorWrapper &wrapper) {
    out << "(";
    for (auto& element : wrapper.vector) {
      out << element;
    }
    out << ")";

    return out;
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

  bool IsOneGreaterThenTwoOfLength(unsigned int one, unsigned int two, unsigned int length, bool is_reverse) {
    std::map<char, char> init_map;
    MapWrapper<char, char> reverse_nucleobases{init_map};
    reverse_nucleobases.Set('1', '2');
    reverse_nucleobases.Set('2', '1');
    reverse_nucleobases.Set('3', '0');
    reverse_nucleobases.Set('0', '3');

    char char_one;
    char char_two;
    for (unsigned int i = 0; i < length; i++) {
      char_one = this->vector[one + i];
      char_two = this->vector[two + i];

      if (is_reverse) {
        char_one = reverse_nucleobases.Get(char_one);
        char_two = reverse_nucleobases.Get(char_two);
      }

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

  void Clear() {
    this->vector.clear();
  }
};



#endif // VECTOR_WRAPPER_TEMPLATE
