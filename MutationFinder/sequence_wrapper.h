#ifndef SEQUENCE_WRAPPER
#define SEQUENCE_WRAPPER

//Aliases

//Includes
#include "standard_include.h"
#include "string_wrapper.h"
#include "vector_helper.h"
#include "map_wrapper_template.h"

//Declarations
class SequenceWrapper {
private:
  std::vector<char> description;
  std::vector<char> sequence;

public:
  SequenceWrapper(std::vector<char> &description, std::vector<char> &sequence) :
    description(description),
    sequence(sequence) {
  }



  void AppendDescription(StringWrapper &string) {
    for (unsigned int i = 0; i < string.Length(); i++) {
      char character = string.GetChar(i);
      description.push_back(character);
    }
  }

  void AppendSequence(StringWrapper &string) {
    for (unsigned int i = 0; i < string.Length(); i++) {
      char character = string.GetChar(i);
      sequence.push_back(character);
    }
  }



  MapWrapper<char, int> CountOccurrences() {
    std::map<char, int> map;
    MapWrapper<char, int> occurrences{map};

    for (unsigned int i = 0; i < Length(sequence); i++) {
      char character = sequence[i];
      if (occurrences.IsExists(character)) {
        int count_plus_one = occurrences.Get(character) + 1;
        occurrences.Set(character, count_plus_one);
      } else {
        int one = 1;
        occurrences.Set(character, one);
      }
    }

    return occurrences;
  }



  void Print() {
    std::cout << "-.-.-.-.-" << std::endl;
    std::cout << "Description:";

    for (auto& element : description) {
      std::cout << element;
    }

    std::cout << std::endl;
    std::cout << "Sequence:";

    unsigned int len = Length(sequence);
    unsigned int ten = 10;
    unsigned int up_to_ten = std::min(ten, len);
    for (unsigned int i = 0; i < up_to_ten; i++) {
      std::cout << sequence[i];
    }

    std::cout << "..." << std::endl;
    std::cout << "-.-.-.-.-" << std::endl;
  }
};

#endif
