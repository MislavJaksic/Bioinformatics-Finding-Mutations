#ifndef KMER_KEY
#define KMER_KEY

//Includes
#include <iostream>

#include "Kmer.h"

//Declarations
class KmerKey {
private:
  Kmer kmer;
  bool is_on_reverse_helix;

public:
  KmerKey() :
    kmer{},
    is_on_reverse_helix{} {
  }

  KmerKey(const Kmer &init_kmer, const bool &init_is_reverse) :
    kmer(init_kmer),
    is_on_reverse_helix(init_is_reverse) {
  }

  friend std::ostream& operator<< (std::ostream &out, const KmerKey &key); //for printing
  friend bool operator== (const KmerKey &key_A, const KmerKey &key_B);
  friend bool operator< (const KmerKey &key_A, const KmerKey &key_B);

  const Kmer& GetKmer() const;
  const bool& GetIsReverse() const;
};

#endif
