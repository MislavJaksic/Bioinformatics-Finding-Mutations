#ifndef KMER_KEY
#define KMER_KEY

//Includes
#include "standard_include.h"
#include "kmer.h"

class KmerKey {
private:
  Kmer kmer;
  bool is_on_reverse_helix;

public:
  KmerKey(Kmer &init_kmer, bool &init_is_on_reverse_helix) :
    kmer(init_kmer),
    is_on_reverse_helix(init_is_on_reverse_helix) {
  }

  friend bool operator< (const KmerKey &key_A, const KmerKey &key_B) {
    Kmer kmer_A = key_A.kmer;
    Kmer kmer_B = key_B.kmer;

    unsigned int length_A = kmer_A.Length();
    unsigned int length_B = kmer_B.Length();

    if (length_A < length_B) {
      return true;
    } else if (length_A > length_B) {
      return false;
    }

    for (unsigned int i = 0; i < length_A; i++) {
      if (kmer_A[i] > kmer_B[i]) {
        return false;
      } else if (kmer_A[i] < kmer_B[i]) {
        return true;
      }
    }

    bool is_reverse_A = key_A.is_on_reverse_helix;
    bool is_reverse_B = key_B.is_on_reverse_helix;

    if (is_reverse_A < is_reverse_B) {
      return true;
    } else {
      return false;
    }

    return true;
  }

  friend std::ostream& operator<< (std::ostream &out, const KmerKey &key) {
    out << "(" << key.kmer << ", " << key.is_on_reverse_helix << ")";

    return out;
  }



  void Print() {
    std::cout << "(";
    this->kmer.Print();
    std::cout << ", ";
    std::cout << this->is_on_reverse_helix;
    std::cout << ")" << std::endl;
  }
};



#endif // KMER_TRIPLE
