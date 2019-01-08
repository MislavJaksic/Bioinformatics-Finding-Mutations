#include "KmerTriple.h"



std::ostream& operator<< (std::ostream &out, const KmerTriple &triple) {
  out << "(";
  out << triple.key;
  out << ",";
  out << triple.position;
  out << ")";

  return out;
}



const KmerKey& KmerTriple::GetKey() const {
  return this->key;
}

const unsigned int& KmerTriple::GetPosition() const {
  return this->position;
}
