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

  KmerKey& GetKey();
  const KmerKey& GetKey() const;
  Kmer& GetKmer();
  const Kmer& GetKmer() const;
  bool& GetIsReverse();
  const bool& GetIsReverse() const;
  unsigned int& GetPosition();
  const unsigned int& GetPosition() const;
};

#endif
