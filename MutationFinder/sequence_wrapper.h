#ifndef SEQUENCE_WRAPPER
#define SEQUENCE_WRAPPER

//Aliases

//Includes
#include "standard_include.h"
#include "string_wrapper.h"
#include "map_wrapper_template.h"
#include "vector_char_wrapper.h"
#include "kmer_triple.h"
#include "kmer_index.h"



//Declarations
class SequenceWrapper {
private:
  VectorWrapper description;
  VectorWrapper sequence;
  std::vector<KmerTriple> minimizers;

public:
  KmerIndex index;

  SequenceWrapper(VectorWrapper &description, VectorWrapper &sequence, std::vector<KmerTriple> &minimizers, KmerIndex &index) :
    description(description),
    sequence(sequence),
    minimizers(minimizers),
    index(index) {

  }



  void AppendDescription(StringWrapper &string) {
    description.Append(string);
  }

  void AppendSequence(StringWrapper &string) {
    sequence.Append(string);
  }



  /*
  Given an imaginary sequence 1003332222 and its reverse 2330001111, window length 5 and kmer length 3
  the following minimizers would be extracted:
  10033 -> 003
  23300

  00333
  33000 -> 000

  03332
  30001 -> 000

  33322 ->
  00011 -> 000

  33222
  00111 -> 001

  32222
  01111 -> 011
  Position duplicates are removed automatically.
  */
  void ExtractMinimizerKmersOfLengthInWindow(unsigned int kmer_length, unsigned int window_length) {
    unsigned int window_position = 0;
    unsigned int true_minimizer_position = 0;
    unsigned int reverse_minimizer_position = 0;

    unsigned int max_window = this->sequence.Length() - window_length + 1;

    while (window_position < max_window) {
      true_minimizer_position = this->FindKmerMinimizerInWindowOfLength(kmer_length, window_position, window_length, false);
      reverse_minimizer_position = this->FindKmerMinimizerInWindowOfLength(kmer_length, window_position, window_length, true);

      if (this->IsTrueBiggerThenReverseOfLength(true_minimizer_position, reverse_minimizer_position, kmer_length)) {
        this->AppendMinimizer(reverse_minimizer_position, kmer_length, true);
        window_position = window_position + (reverse_minimizer_position - window_position) + 1;
      } else {
        this->AppendMinimizer(true_minimizer_position, kmer_length, false);
        window_position = window_position + (true_minimizer_position - window_position) + 1;
      }

    }

    //TODO solve the skip the last window problem
    //unsigned int correct_cutoff_position = this->FindKmerMinimizerInWindowOfLength(kmer_length, max_window - 1, window_length, false);
    //if (minimizer_position != correct_cutoff_position) {
    //this->AppendMinimizer(FindKmerMinimizerInWindowOfLength(kmer_length, max_window - 1, window_length, false), kmer_length);
    //}

    this->Shrink();
  }

  unsigned int FindKmerMinimizerInWindowOfLength(unsigned int minimizer_length, unsigned int window_position, unsigned int window_length, bool is_reverse) {
    unsigned int candidate = window_position;

    unsigned int max_length = window_length - minimizer_length + 1;

    for (unsigned int i = 0; i < max_length; i++) {
      if (this->IsCandidateBiggerThenCurrentOfLength(candidate, window_position + i, minimizer_length, is_reverse)) {
        candidate = window_position + i;
      }
    }
    return candidate;
  }

  bool IsCandidateBiggerThenCurrentOfLength(unsigned int one, unsigned int two, unsigned int length, bool is_reverse) {
    return this->sequence.IsOneGreaterThenTwoOfLength(one, two, length, is_reverse);
  }

  void AppendMinimizer(unsigned int position, unsigned int length, bool is_reverse) {
    std::map<char, char> init_map;
    MapWrapper<char, char> reverse_nucleobases{init_map};
    reverse_nucleobases.Set('1', '2');
    reverse_nucleobases.Set('2', '1');
    reverse_nucleobases.Set('3', '0');
    reverse_nucleobases.Set('0', '3');

    std::vector<char> vector;
    char character;
    if (is_reverse) {
      for (unsigned int i = 0; i < length; i++) {
        character = reverse_nucleobases.Get(this->sequence[position + i]);
        vector.push_back(character);
      }
    } else {
      for (unsigned int i = 0; i < length; i++) {
        character = this->sequence[position + i];
        vector.push_back(character);
      }
    }
    Kmer kmer{vector};

    KmerTriple triple{kmer, is_reverse, position};

    minimizers.push_back(triple);
  }

  bool IsTrueBiggerThenReverseOfLength(unsigned int true_position, unsigned int reverse_position, unsigned int length) {
    std::map<char, char> init_map;
    MapWrapper<char, char> reverse_nucleobases{init_map};
    reverse_nucleobases.Set('1', '2');
    reverse_nucleobases.Set('2', '1');
    reverse_nucleobases.Set('3', '0');
    reverse_nucleobases.Set('0', '3');

    char char_one;
    char char_two;
    for (unsigned int i = 0; i < length; i++) {
      char_one = this->sequence[true_position + i];
      char_two = reverse_nucleobases.Get(this->sequence[reverse_position + i]);

      if (char_one > char_two) {
        return true;
      } else if (char_one < char_two) {
        return false;
      }
    }
    return false;
  }



  void IndexKmerMinimizers() {
    std::vector<char> init_vector;
    Kmer init_kmer{init_vector};
    bool init_is_reverse = false;
    unsigned int init_position = 0;
    KmerTriple triple{init_kmer, init_is_reverse, init_position};

    for (unsigned int i = 0; i < minimizers.size(); i++) {
      triple = minimizers[i];
      init_kmer = triple.GetKmer();
      init_is_reverse = triple.GetIsReverse();
      init_position = triple.GetPosition();

      KmerKey key{init_kmer, init_is_reverse};
      index.Add(key, init_position);
    }
  }



  void TransformSequence(MapWrapper<char, char> &map) {
    this->sequence.Transform(map);
  }

  MapWrapper<char, int> CountSequenceValues() {
    MapWrapper<char, int> occurrences = this->sequence.CountValues();

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

  void PrintMinimizers() {
    for (unsigned int i = 0; i < this->minimizers.size(); i++) {
      this->minimizers[i].Print();
    }
  }

  void PrintIndex() {
    this->index.Print();
  }



  void Shrink() {
    this->description.Shrink();
    this->sequence.Shrink();
    this->minimizers.shrink_to_fit();
  }
};

#endif
