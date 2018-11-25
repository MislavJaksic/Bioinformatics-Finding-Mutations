#include "map_helper.h"

void UpsertKeyValue(char &key, int &value, std::map<char, int> &map) {
  map[key] = value;
}

int GetValueForKey(char &key, std::map<char, int> &map) {
  return map.find(key)->second;
}



void Print(std::map<char, int> &map) {
  std::map<char, int>::iterator it = map.begin();
  while (it != map.end()) {
    std::cout << it->first << " :: " << it->second << std::endl;
    it++;
  }
}



bool IsKeyExists(char &key, std::map<char, int> &map) {
  if (map.find(key) == map.end()) {
    return false;
  }
  return true;
}

