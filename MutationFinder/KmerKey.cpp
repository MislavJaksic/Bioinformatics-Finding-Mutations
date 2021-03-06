/*
Author: Mislav Jaksic
*/

#include "KmerKey.h"



std::ostream& operator<< (std::ostream &out, const KmerKey &key) {
  out << "(";
  out << key.kmer;
  out << ",";
  out << key.is_on_reverse_helix;
  out << ")";

  return out;
}

bool operator== (const KmerKey &key_A, const KmerKey &key_B) {
  if (key_A.kmer == key_B.kmer) {
    if (key_A.is_on_reverse_helix == key_B.is_on_reverse_helix) {
      return true;
    }
  }
  return false;
}

bool operator< (const KmerKey &key_A, const KmerKey &key_B) {
  if (key_A.kmer == key_B.kmer) {
    if (key_A.is_on_reverse_helix < key_B.is_on_reverse_helix) {
      return true;
    }
    return false;
  } else {
    if (key_A.kmer < key_B.kmer) {
      return true;
    }
    return false;
  }
}



Kmer& KmerKey::GetKmer() {
  return this->kmer;
}

const Kmer& KmerKey::GetKmer() const {
  return this->kmer;
}

bool& KmerKey::GetIsReverse() {
  return this->is_on_reverse_helix;
}

const bool& KmerKey::GetIsReverse() const {
  return this->is_on_reverse_helix;
}
