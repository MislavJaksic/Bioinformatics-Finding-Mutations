#include "vector_helper.h"

std::vector<char>& AppendStringWrapperToVector(StringWrapper &string, std::vector<char> &vector) {
  for (unsigned int i = 0; i < string.Length(); i++) {
    char character = string.GetChar(i);
    vector.push_back(character);
  }
  return vector;
}



unsigned int Length(std::vector<char> &vector) {
  return vector.size();
}
