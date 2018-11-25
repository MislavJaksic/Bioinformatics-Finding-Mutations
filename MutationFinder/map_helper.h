#ifndef MAP_HELPER
#define MAP_HELPER

//Aliases
#include "type_aliases.h"

//Includes
#include "standard_include.h"

//Declarations
void UpsertKeyValue(char &key, int &value, std::map<char, int> &map);
int GetValueForKey(char &key, std::map<char, int> &map);

void Print(std::map<char, int> &map);

bool IsKeyExists(char &key, std::map<char, int> &map);


#endif // MAP_HELPER
