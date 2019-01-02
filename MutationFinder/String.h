//Header guard start
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
  //for "String string{"hello"}" init
  String(const char* s) :
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
  String& operator= (const char* s); //for "string = "hello""
  friend std::ostream& operator<< (std::ostream &out, const String &string); //for printing

  std::string GetString() const;

  unsigned int Length() const;

  bool IsCharAt(const char character, const unsigned int index);
  bool IsEmpty();
  bool IsNotEmpty();

  void Clear();
};

//Header guard end
#endif
