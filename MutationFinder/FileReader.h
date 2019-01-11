#ifndef FILE_READER
#define FILE_READER

//Includes
#include <iostream>
#include <fstream>

#include "String.h"
#include <cstdlib>

//Declarations
class FileReader {
private:
  std::ifstream stream;

  void HandleFailError(const String &file_name);
  void HandleBadError(const String &file_name);

public:
  FileReader(const String &file_name) :
    stream{file_name.GetString()} {
    this->HandleFailError(file_name);
    this->HandleBadError(file_name);
  }

  ~FileReader() {
    this->Close();
  }

  String ReadLine();

  bool IsFlagsUnset();
  bool IsEOF();
  bool IsFail();
  bool IsBad();
  void ResetFlags();

  void Close();
};

#endif

