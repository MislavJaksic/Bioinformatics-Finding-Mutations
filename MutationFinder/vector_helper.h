#ifndef VECTOR_HELPER
#define VECTOR_HELPER

//Aliases

//Includes
#include "standard_include.h"
#include "string_wrapper.h"

//Declarations
std::vector<char>& AppendStringWrapperToVector(StringWrapper &string, std::vector<char> &vector);

unsigned int Length(std::vector<char> &vector);

#endif // VECTOR_HELPER
