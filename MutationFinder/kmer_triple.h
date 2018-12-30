#ifndef KMER_TRIPLE
#define KMER_TRIPLE

//Includes
#include "standard_include.h"
#include "kmer.h"

class KmerTriple {
private:
  Kmer kmer;
  bool is_on_reverse_helix;
  unsigned int position_in_string;

public:
  KmerTriple(Kmer &init_kmer, bool &init_is_on_reverse_helix, unsigned int &init_position_in_string) :
    kmer(init_kmer),
    is_on_reverse_helix(init_is_on_reverse_helix),
    position_in_string(init_position_in_string) {
  }

  Kmer GetKmer() {
    return this->kmer;
  }

  bool GetIsReverse() {
    return this->is_on_reverse_helix;
  }

  unsigned int GetPosition() {
    return this->position_in_string;
  }



  void Print() {
    std::cout << "(";
    this->kmer.Print();
    std::cout << ", ";
    std::cout << this->is_on_reverse_helix;
    std::cout << ", ";
    std::cout << this->position_in_string;
    std::cout << ")" << std::endl;
  }
};



#endif // KMER_TRIPLE
