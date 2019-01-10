#include "KmerTriple.h"



std::ostream& operator<< (std::ostream &out, const KmerTriple &triple) {
  out << "(";
  out << triple.key;
  out << ",";
  out << triple.position;
  out << ")";

  return out;
}

bool operator< (const KmerTriple &triple_A, const KmerTriple &triple_B) {
  if (triple_A.key == triple_B.key) {
    if (triple_A.position < triple_B.position) {
      return true;
    }
    return false;
  } else {
    if (triple_A.key < triple_B.key) {
      return true;
    }
    return false;
  }
}

const KmerKey& KmerTriple::GetKey() const {
  return this->key;
}

const Kmer& KmerTriple::GetKmer() const {
  return this->key.GetKmer();
}

const bool& KmerTriple::GetIsReverse() const {
  return this->key.GetIsReverse();
}



const unsigned int& KmerTriple::GetPosition() const {
  return this->position;
}

/*
KmerKey KmerTriple::GetKey() const {
  return this->key;
}

unsigned int KmerTriple::GetPosition() const {
  return this->position;
}
*/
