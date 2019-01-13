/*
Author: Mislav Jaksic
*/

#ifndef MAP_WRAPPER
#define MAP_WRAPPER

//Includes
#include <map>

//Declarations
template <class K, class V>
class Map {
private:
  std::map<K, V> key_values;

public:
  Map() :
    key_values{} {
  }

  ~Map() {
    this->Clear();
  }

  V& operator[](const K &key) {
    return this->key_values[key];
  }

  const V& operator[](const K &key) const {
    return this->key_values[key];
  }



  unsigned int IsExists(const K &key) const {
    return this->key_values.count(key);
  }



  void Clear() {
    this->key_values.clear();
  }
};

#endif

