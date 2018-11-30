#ifndef KMER_H
#define KMER_H

//Includes
#include "vector_wrapper_template.h"

class Kmer : public VectorWrapper {
public:
  Kmer(std::vector<char> &vector) :
    VectorWrapper(vector) {
  }
};


#endif // KMER_H
