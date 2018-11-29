#ifndef KMER_TRIPLE
#define KMER_TRIPLE

//Includes
#include "standard_include.h"
#include "kmer.h"

class KmerTriple {
private:
  Kmer kmer;
  int string_id;
  int position_in_string;

public:
  KmerTriple(Kmer init_kmer, int init_string_id, int init_position_in_string) :
    kmer(init_kmer),
    string_id(init_string_id),
    position_in_string(init_position_in_string) {
  }

  void Print() {
    std::cout << "(";
    this->kmer.Print();
    std::cout << ", ";
    std::cout << this->string_id;
    std::cout << ", ";
    std::cout << this->position_in_string;
    std::cout << ")" << std::endl;
  }


};



#endif // KMER_TRIPLE
