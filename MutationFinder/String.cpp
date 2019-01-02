#include "String.h"



char& String::operator[](const unsigned int index) {
  return this->string[index];
}

const char& String::operator[](const unsigned int index) const {
  return this->string[index];
}

String& String::operator=(const char* s) {
  this->string = s;
  return *this;
}

std::ostream& operator<< (std::ostream &out, const String &string) {
  out << string.string;
  return out;
}



std::string String::GetString() const {
  return this->string;
}



unsigned int String::Length() const {
  return this->string.length();
}



bool String::IsCharAt(const char character, const unsigned int index) {
  if (this->string[index] == character) {
    return true;
  }
  return false;
}

bool String::IsEmpty() {
  if (this->string.empty()) {
    return true;
  }
  return false;
}

bool String::IsNotEmpty() {
  if (this->IsEmpty()) {
    return false;
  }
  return true;
}



void String::Clear() {
  this->string.clear();
}
