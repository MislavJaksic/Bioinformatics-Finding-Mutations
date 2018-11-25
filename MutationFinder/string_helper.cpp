#include "string_helper.h"

bool IsEmpty(String &string) {
  if (string.empty()) {
    return true;
  }
  return false;
}

bool IsFull(String &string) {
  if (string.empty()) {
    return false;
  }
  return true;
}

bool IsBeginsWithGreaterThen(String &string) {
  if (string[0] == '>') {
    return true;
  }
  return false;
}



unsigned int Length(String &string) {
  return string.length();
}



void Clear(String &string) {
  string.clear();
}
