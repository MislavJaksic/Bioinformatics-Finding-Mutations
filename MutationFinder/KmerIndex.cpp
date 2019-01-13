/*
Author: Mislav Jaksic
*/

#include "KmerIndex.h"



unsigned int KmerIndex::max_print{20};



std::vector<unsigned int>& KmerIndex::operator[](KmerKey &&key) {
  return this->index[key];
}

std::vector<unsigned int>& KmerIndex::operator[](const KmerKey &key) {
  return this->index[key];
}

std::ostream& operator<< (std::ostream &out, const KmerIndex &kmer_index) {
  unsigned int counter = 0;

  std::cout << "[";
  for (auto it = kmer_index.index.cbegin(); it != kmer_index.index.cend(); ++it) {
    std::cout << it->first;
    std::cout << " => ";

    out << "[";
    for (unsigned int i = 0; i < it->second.size(); i++) {
      out << it->second[i];
      if (i == it->second.size()) {
        break;
      }
      if (i == KmerIndex::max_print) {
        const unsigned int difference = it->second.size() - KmerIndex::max_print;
        out << " and " << difference << " more";
        break;
      }
      out << ",";
    }
    out << "]";

    if (it == kmer_index.index.cend()) {
      break;
    }
    if (counter == KmerIndex::max_print) {
      out << " and " << "a lot" << " more";
      break;
    }
    out << ",";

    out << std::endl;

    counter++;
  }

  std::cout << "]";

  return out;
}



void KmerIndex::Add(const KmerKey &key, const unsigned int &value) {
  if (this->IsExists(key)) {
    this->index[key].push_back(value);
  } else {
    std::vector<unsigned int> vector{value};
    this->index[key] = vector;
  }
}



bool KmerIndex::IsExists(const KmerKey &key) const {
  if (index.count(key)) {
    return true;
  }
  return false;
}



void KmerIndex::Shrink() {
  for (auto it = this->index.begin(); it != this->index.end(); ++it) {
    it->second.shrink_to_fit();
  }
}

void KmerIndex::Clear() {
  this->index.clear();
}
