#ifndef SEQUENCE_MAPPER
#define SEQUENCE_MAPPER

#include <iostream>

#include "Sequence.h"
#include <cstdlib>
#include <cstddef>

//Declarations
struct mutation {
  char mutation_character;
  unsigned int position;
  char nucleobase;
};

struct cell {
  int cost{0};
  cell *parrent = nullptr;
};

class SequenceMapper {

public:
  static std::map<char, char> reverse_nucleobase;
  static int missmatch_1;
  static int missmatch_2;
  static int indel;
  static std::map<std::tuple<char, char>, int> pam;

  SequenceMapper() {
  }

  std::vector<unsigned int> getMatchingPositions(Sequence &sequence_A, Sequence &sequence_B);

  std::vector<mutation> getMutations(Sequence &sequence_A, Sequence &sequence_B);
  std::vector<mutation> getGlobalMutations(Sequence &sequence_A, Sequence &sequence_B, int position_A, int N, int position_B, int M);

  //static std::map<std::tuple<char, char>, int> initPam();
};

#endif // SEQUENCE_MAPPER
