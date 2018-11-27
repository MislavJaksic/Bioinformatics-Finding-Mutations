#ifndef STRING_WRAPPER
#define STRING_WRAPPER

//Aliases

//Includes
#include "standard_include.h"

//Declarations
class StringWrapper {
private:
  std::string string;

public:
  StringWrapper(std::string string) :
    string(string) {
  }

  void Set(std::string string) {
    this->string = string;
  }

  std::string Get() {
    return this->string;
  }

  char GetChar(unsigned int &i) {
    return this->string[i];
  }


  bool IsEmpty() {
    if (this->string.empty()) {
      return true;
    }
    return false;
  }

  bool IsFull() {
    if (this->string.empty()) {
      return false;
    }
    return true;
  }

  bool IsBeginsWithGreaterThen() {
    if (this->string[0] == '>') {
      return true;
    }
    return false;
  }



  unsigned int Length() {
    return this->string.length();
  }



  void Clear() {
    this->string.clear();
  }

};

#endif
