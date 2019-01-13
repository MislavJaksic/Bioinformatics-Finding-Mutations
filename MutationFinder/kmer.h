/*
Author: Mislav Jaksic
*/

#ifndef KMER
#define KMER

//Includes
#include "CharVector.h"

//Declarations
class Kmer : public CharVector {
public:
  Kmer() :
    CharVector() {
  }

  Kmer(const std::initializer_list<char> &il) :
    CharVector(il) {
  }

};

#endif
