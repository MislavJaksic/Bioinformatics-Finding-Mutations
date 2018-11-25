//Header guard start
#ifndef FASTA_WRAPPER
#define FASTA_WRAPPER

//Aliases
#include "type_aliases.h"

//Includes
#include "standard_include.h"
#include "string_helper.h"
#include "vector_helper.h"
#include "map_helper.h"

//Declarations
class FastaWrapper {
public:
  CharVector description;
  CharVector sequence;

  FastaWrapper(CharVector &description, CharVector &sequence);

  void AppendDescription(String &string);
  void AppendSequence(String &string);

  std::map<char, int> CountOccurrences();

  void Print();
};

//Header guard end
#endif // FASTA_WRAPPER
