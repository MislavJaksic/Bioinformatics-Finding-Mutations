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

  String(const char* s) : //for "String string{"hello"}" init
    string{s} {
  }

  String(const std::string &init_string) :
    string{init_string} {
  }

  ~String() {
    this->Clear();
  }

  char& operator[](const unsigned int index); //for string[5]
  const char& operator[](const unsigned int index) const;
  String& operator= (const char* s); //for "string = "hello""
  friend std::ostream& operator<< (std::ostream &out, const String &string); //for printing

  const std::string& GetString() const;

  unsigned int Length() const;

  bool IsCharAt(const char character, const unsigned int index);
  bool IsEmpty();
  bool IsNotEmpty();

  void Shrink();
  void Clear();
};

//Header guard end
#endif
