/*
Author: Mislav Jaksic
*/

#ifndef KMER_INDEX
#define KMER_INDEX

//Includes
#include <vector>
#include <map>

#include "KmerKey.h"

//Declarations
class KmerIndex {
private:
  std::map<KmerKey, std::vector<unsigned int>> index;

  static unsigned int max_print;

public:
  KmerIndex() :
    index{} {
  }

  std::vector<unsigned int>& operator[](KmerKey &&key);
  std::vector<unsigned int>& operator[](const KmerKey &key);
  friend std::ostream& operator<< (std::ostream &out, const KmerIndex &index);

  void Add(const KmerKey &key, const unsigned int &value);

  bool IsExists(const KmerKey &key) const;

  void Shrink();
  void Clear();
};

#endif
