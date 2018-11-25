#ifndef STRING_HELPER
#define STRING_HELPER

//Aliases
#include "type_aliases.h"

//Includes
#include "standard_include.h"

//Declarations
bool IsEmpty(String &string);
bool IsFull(String &string);
bool IsBeginsWithGreaterThen(String &string);

unsigned int Length(String &string);

void Clear(String &string);

#endif // STRING_HELPER
