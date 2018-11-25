#include "vector_helper.h"

CharVector& AppendStringToVector(String &string, CharVector &vector) {
  for (unsigned int i = 0; i < Length(string); i++) {
    char character = string[i];
    vector.push_back(character);
  }
  return vector;
}



unsigned int Length(CharVector &vector) {
  return vector.size();
}
