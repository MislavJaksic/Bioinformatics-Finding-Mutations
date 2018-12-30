#ifndef KMER_INDEX
#define KMER_INDEX

//Includes
#include "map_wrapper_template.h"
#include "kmer_key.h"



class KmerIndex {
private:
  MapWrapper<KmerKey, std::vector<unsigned int>> index;
public:
  KmerIndex(MapWrapper<KmerKey, std::vector<unsigned int>> &init_index) :
    index(init_index) {
  }

  void Add(KmerKey key, unsigned int value) {
    std::vector<unsigned int> vector;

    if (index.IsExists(key)) {
      vector = index.Get(key);
    }
    vector.push_back(value);
    this->index.Set(key, vector);
  }

  std::vector<unsigned int> Get(KmerKey &key) {
    return this->index.Get(key);
  }

  bool IsExists(KmerKey &key) {
    if (index.IsExists(key)) {
      return true;
    }
    return false;
  }



  void Print() {
    std::map<KmerKey, std::vector<unsigned int>>::iterator start_it = this->index.GetStartIterator();
    std::map<KmerKey, std::vector<unsigned int>>::iterator end_it = this->index.GetEndIterator();
    while (start_it != end_it) {
      std::cout << start_it->first;
      std::cout << " :: ";
      std::cout << "[";
      std::vector<unsigned int> vector = start_it->second;
      for (auto& element : vector) {
        std::cout << element;
        std::cout << ", ";
      }
      std::cout << "]";
      std::cout << std::endl;
      start_it++;
    }
  }
};


#endif // KMER_H
