#ifndef KMER_TRIPLE
#define KMER_TRIPLE

//Includes
#include <iostream>

#include "KmerKey.h"

//Declarations
class KmerTriple {
private:
  KmerKey key;
  unsigned int position;

public:
  KmerTriple() :
    key{},
    position{} {
  }

  KmerTriple(const KmerKey &init_key, const unsigned int &init_position) :
    key(init_key),
    position(init_position) {
  }

  friend std::ostream& operator<< (std::ostream &out, const KmerTriple &triple);

  const KmerKey& GetKey() const;
  const unsigned int& GetPosition() const;
};

#endif
