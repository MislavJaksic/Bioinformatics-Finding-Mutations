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
  friend bool operator< (const KmerTriple &triple_A, const KmerTriple &triple_B);


  const KmerKey& GetKey() const;
  const Kmer& GetKmer() const;
  const bool& GetIsReverse() const;

  const unsigned int& GetPosition() const;
  //KmerKey GetKey() const;
  //unsigned int GetPosition() const;
};

#endif
