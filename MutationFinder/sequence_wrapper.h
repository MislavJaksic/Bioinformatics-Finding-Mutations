#ifndef SEQUENCE_WRAPPER
#define SEQUENCE_WRAPPER

//Aliases

//Includes
#include "standard_include.h"
#include "string_wrapper.h"
#include "map_wrapper_template.h"
#include "vector_wrapper_template.h"
#include "kmer_triple.h"

//Declarations
class SequenceWrapper {
private:
  VectorWrapper description;
  VectorWrapper sequence;
  std::vector<KmerTriple> minimizers;

public:
  SequenceWrapper(VectorWrapper &description, VectorWrapper &sequence, std::vector<KmerTriple> &minimizers) :
    description(description),
    sequence(sequence),
    minimizers(minimizers) {
  }



  void AppendDescription(StringWrapper &string) {
    char character;
    for (unsigned int i = 0; i < string.Length(); i++) {
      character = string.GetChar(i);
      description.Append(character);
    }
  }

  void AppendSequence(StringWrapper &string) {
    char character;
    for (unsigned int i = 0; i < string.Length(); i++) {
      character = string.GetChar(i);
      sequence.Append(character);
    }
  }



  void FindMinimizers(unsigned int &window_length, unsigned int &kmer_length) {
    /*unsigned int a = 0;
    unsigned int b = 0;
    unsigned int sequence_length = this->sequence.Length();

    std::vector<char> init_vector;
    Kmer minimizer_candidate{init_vector};
    Kmer current_kmer{init_vector};*/


    /*while (a < sequence_length) {
      if (minimizer_candidate[b] > this->sequence[a + b]) {
        for (unsigned int c = 0; c < kmer_length; c++) {
          //minimizer_candidate[c] =
        }
      }
      a++;
    }*/
    std::cout << window_length << std::endl;
    std::cout << kmer_length << std::endl;
    //TODO
  }



  void TransformSequence(MapWrapper<char, char> &map) {
    sequence.Transform(map);
  }

  MapWrapper<char, int> CountOccurrences() {
    std::map<char, int> init_map;
    MapWrapper<char, int> occurrences{init_map};

    char character;
    for (unsigned int i = 0; i < sequence.Length(); i++) {
      character = sequence[i];
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
    std::cout << "Description:";

    description.Print();
    std::cout << std::endl;

    std::cout << "Sequence:";

    unsigned int len = sequence.Length();
    unsigned int ten = 10;
    unsigned int up_to_ten = std::min(ten, len);
    for (unsigned int i = 0; i < up_to_ten; i++) {
      std::cout << sequence[i];
    }
    std::cout << "..." << std::endl;

  }
};

#endif
