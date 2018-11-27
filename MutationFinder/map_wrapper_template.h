#ifndef MAP_WRAPPER_TEMPLATE
#define MAP_WRAPPER_TEMPLATE

//Aliases

//Includes
#include "standard_include.h"

//Declarations
template <class K, class V>
class MapWrapper {
public:
  std::map<K, V> map;

  MapWrapper(std::map<K, V> map) :
    map(map) {
  }

  void Set(K &key, V &value) {
    map[key] = value;
  }

  int Get(K &key) {
    return map.find(key)->second;
  }

  bool IsExists(K &key) {
    if (map.find(key) == map.end()) {
      return false;
    }
    return true;
  }



  void Print() {
    typename std::map<K, V>::iterator it = map.begin();
    while (it != map.end()) {
      std::cout << it->first << " :: " << it->second << std::endl;
      it++;
    }
  }
};

#endif
