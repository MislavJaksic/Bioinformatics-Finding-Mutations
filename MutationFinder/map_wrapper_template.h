#ifndef MAP_WRAPPER_TEMPLATE
#define MAP_WRAPPER_TEMPLATE

//Aliases

//Includes
#include "standard_include.h"

//Declarations
template <class K, class V>
class MapWrapper {
private:
  std::map<K, V> map;
public:
  MapWrapper(std::map<K, V> &map) :
    map(map) {
  }

  void Set(K key, V value) {
    map[key] = value;
  }

  V Get(K &key) {
    return map.find(key)->second;
  }

  bool IsExists(K &key) {
    if (map.find(key) == map.end()) {
      return false;
    }
    return true;
  }



  typename std::map<K, V>::iterator GetStartIterator() {
    return map.begin();
  }

  typename std::map<K, V>::iterator GetEndIterator() {
    return map.end();
  }



  void Print() {
    typename std::map<K, V>::iterator it = this->GetStartIterator();
    while (it != map.end()) {
      std::cout << it->first << " :: " << it->second << std::endl;
      it++;
    }
  }
};

#endif
