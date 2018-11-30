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
    description.Append(string);
  }

  void AppendSequence(StringWrapper &string) {
    sequence.Append(string);
  }



  /*
  Given an imaginary sequence 1003332222, window length 5 and kmer length 3
  the following minimizers would be extracted:
  10033 -> 003
  00333 -> 003
  03332 -> 033
  33322 -> 322
  33222 -> 222
  32222 -> 222
  Position duplicates are removed automatically.
  */
  void ExtractMinimizerKmersOfLengthInWindow(unsigned int kmer_length, unsigned int window_length) {
    unsigned int window_position = 0;
    unsigned int minimizer_position = 0;

    unsigned int max_window = this->sequence.Length() - window_length + 1;

    while (window_position < max_window) {
      minimizer_position = this->FindKmerMinimizerInWindowOfLength(kmer_length, window_position, window_length);
      this->AppendMinimizer(minimizer_position, kmer_length);

      window_position = window_position + (minimizer_position - window_position) + 1;
    }

    unsigned int correct_cutoff_position = this->FindKmerMinimizerInWindowOfLength(kmer_length, max_window - 1, window_length);
    if (minimizer_position != correct_cutoff_position) {
      this->AppendMinimizer(FindKmerMinimizerInWindowOfLength(kmer_length, max_window - 1, window_length), kmer_length);
    }

    this->Shrink();
  }

  unsigned int FindKmerMinimizerInWindowOfLength(unsigned int minimizer_length, unsigned int window_position, unsigned int window_length) {
    unsigned int candidate = window_position;

    unsigned int max_length = window_length - minimizer_length + 1;

    for (unsigned int i = 0; i < max_length; i++) {
      if (this->IsCandidateBiggerThenCurrentOfLength(candidate, window_position + i, minimizer_length)) {
        candidate = window_position + i;
      }
    }
    return candidate;
  }

  bool IsCandidateBiggerThenCurrentOfLength(unsigned int one, unsigned int two, unsigned int length) {
    return this->sequence.IsOneGreaterThenTwoOfLength(one, two, length);
  }

  void AppendMinimizer(unsigned int position, unsigned int length) {
    std::vector<char> vector;
    for (unsigned int i = 0; i < length; i++) {
      vector.push_back(this->sequence[position + i]);
    }
    Kmer kmer{vector};
    int minus_one = -1;

    KmerTriple triple{kmer, minus_one, position};

    minimizers.push_back(triple);
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

  void PrintMinimizers(){
    for (unsigned int i = 0; i < this->minimizers.size(); i++) {
      this->minimizers[i].Print();
    }
  }



  void Shrink(){
    this->description.Shrink();
    this->sequence.Shrink();
    this->minimizers.shrink_to_fit();
  }
};

#endif
