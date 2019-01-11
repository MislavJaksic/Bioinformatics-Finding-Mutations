//Header guard start
#ifndef SEQUENCE
#define SEQUENCE

//Includes
#include <map>
#include <algorithm>

#include "String.h"
#include "CharVector.h"
#include "KmerTriple.h"
#include "KmerIndex.h"

//Declarations
class Sequence {
private:
  String description;
  CharVector sequence;

  static unsigned int max_print;
  static std::map<char, char> reverse_nucleobase;

public:
  std::vector<KmerTriple> minimizers;
  KmerIndex minimizer_index;

  Sequence() :
    description{},
    sequence{},
    minimizers{},
    minimizer_index{} {
  }

  Sequence(const String &description, const CharVector &sequence) :
    description{description},
    sequence{sequence},
    minimizers{},
    minimizer_index{} {
  }

  ~Sequence() {
    this->Clear();
  }

  friend std::ostream& operator<< (std::ostream &out, const Sequence &sequence); //for printing

  const String& GetDescription() const;
  const CharVector& GetSequence() const;

  void Transform(const std::map<char,char> char_pairs);
  void Reverse();

  void ExtractMinimizers(unsigned int kmer_length, unsigned int window_length);
  void IndexMinimizers(unsigned int kmer_length, unsigned int window_length);

  unsigned int FindMinimizerOnHelix(unsigned int kmer_length, unsigned int window_position, unsigned int window_length, bool is_reverse_helix);
  bool IsOneBiggerThenTwo(unsigned int one, unsigned int two, unsigned int length, bool is_reverse);
  bool IsTrueBiggerThenReverseOfLength(unsigned int true_position, unsigned int reverse_position, unsigned int length);
  void AppendMinimizer(unsigned int position, unsigned int length, bool is_reverse);
  void SortMinimizers();

  bool IsReverseAlignment(const Sequence& read);
  void CompareWithSequence(const Sequence& read);
  void PrintPositionSurrounding(const unsigned int& position) const;
  void PrintFromTo(const unsigned int& from, const unsigned int& to) const;

  unsigned int Length() const;

  void Shrink();
  void ClearMinimizers();
  void ClearIndex();
  void Clear();

  const std::vector<KmerTriple>& getMinimizers();

  const String& getDescription();
  const CharVector& getSequence();


  unsigned int Length() const;
  void Transform(const std::map<char,char> char_pairs);
  void Reverse();
  bool IsReverseAlignment(const Sequence& read);
  void CompareWithSequence(const Sequence& read);
  void PrintPositionSurrounding(const unsigned int& position) const;
  void PrintFromTo(const unsigned int& from, const unsigned int& to) const;
};

//Header guard end
#endif
