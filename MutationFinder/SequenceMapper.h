#ifndef SEQUENCE_MAPPER
#define SEQUENCE_MAPPER

#include <iostream>
#include <cstdlib>
#include <cstddef>
#include <algorithm>
#include <list>

#include "Sequence.h"

//Declarations
struct mutation {
  char mutation_character;
  unsigned int position;
  char nucleobase;
};

struct point {
  unsigned int x;
  unsigned int y;
};

struct cell {
  int cost;
  int parrent_x;
  int parrent_y;
};

struct mutation_count {
  mutation mut;
  int number;
};

bool operator==(const mutation& mut1, const mutation& mut2);

class SequenceMapper {

public:
  static std::map<char, char> reverse_nucleobase;
  static std::map<char, char> reverse_transformation;
  static int missmatch_1;
  static int missmatch_2;
  static int indel;
  static std::map<std::tuple<char, char>, int> pam;

  SequenceMapper() {
  }

  std::vector<unsigned int> getMatchingPositions(Sequence &sequence_A, Sequence &sequence_B);

  std::vector<point> getAllMatchingPositions(Sequence &sequence_A, Sequence &sequence_B);

  std::list<mutation> getMutations(Sequence &sequence_A, Sequence &sequence_B);
  std::list<mutation> getGlobalMutations(Sequence &sequence_A, Sequence &sequence_B, int position_A,
                                         int N, int position_B, int M, bool reverse_helix, int flag);
  std::list<mutation> getGlobalMutationsReducedSearch(Sequence &sequence_A, Sequence &sequence_B, int position_A,
      int N, int position_B, int M, bool reverse_helix);


  //static std::map<std::tuple<char, char>, int> initPam();
};

#endif // SEQUENCE_MAPPER
