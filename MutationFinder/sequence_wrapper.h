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



  void FindMinimizers(unsigned int window_length, unsigned int kmer_length) {
    unsigned int window_position = 0;
    unsigned int inner_position = 1;
    unsigned int compare_offset;
    unsigned int candidate_position = 0;

    unsigned int sequence_length = this->sequence.Length();
    unsigned int max_window = sequence_length - window_length + 1;
    unsigned int max_inner_position;
    unsigned int max_compare_offset = kmer_length;

    /*std::vector<char> init_vector;
    Kmer minimizer_candidate{init_vector};
    Kmer current_kmer{init_vector};*/

    while (window_position < max_window) {

      max_inner_position = window_position + (window_length - kmer_length) + 1;
      while (inner_position < max_inner_position) {

        compare_offset = 0;
        while (compare_offset < max_compare_offset) {
          if (sequence[inner_position + compare_offset] > sequence[candidate_position + compare_offset]) {

            //new candidate, record last as minimizer
          } else if (sequence[inner_position + compare_offset] < sequence[candidate_position + compare_offset]) {
            break;
          }
          compare_offset++;
        }

        std::cout << "inner:" << inner_position << " " << sequence[inner_position] << std::endl;
        inner_position++;
      }
      /*if (minimizer_candidate[b] > this->sequence[a + b]) {
        for (unsigned int c = 0; c < kmer_length; c++) {
          //minimizer_candidate[c] =
        }
      }*/
      std::cout << "window:" << window_position << std::endl;
      window_position++;
    }
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
