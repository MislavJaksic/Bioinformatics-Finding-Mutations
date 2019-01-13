/*
Author: Mislav Jaksic
*/

#ifndef STRING_WRAPPER
#define STRING_WRAPPER

//Includes
#include <iostream>
#include <string>

//Declarations
class String {
private:
  std::string string;

public:
  String() :
    string() {
  }

  String(const char* s) : //for "String string{"hello"}" init
    string{s} {
  }

  String(const std::string &init_string) :
    string{init_string} {
  }

  ~String() {
    this->Clear();
  }

  char& operator[](const unsigned int index);
  const char& operator[](const unsigned int index) const;
  String& operator= (const char* s);
  friend std::ostream& operator<< (std::ostream &out, const String &string);

  const std::string& GetString() const;

  unsigned int Length() const;

  unsigned int SubstringPosition(const std::string& str);
  unsigned int SubstringPosition(const char* s) const;

  bool IsCharAt(const char character, const unsigned int index);
  bool IsEmpty();
  bool IsNotEmpty();

  void Shrink();
  void Clear();
};

#endif
