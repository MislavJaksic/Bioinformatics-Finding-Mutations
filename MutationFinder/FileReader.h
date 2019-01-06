#ifndef FILE_READER
#define FILE_READER

//Includes
#include <iostream>
#include <fstream>

#include "String.h"

//Declarations
class FileReader {
private:
  std::ifstream stream;

public:
  FileReader(const String &file_name) :
    stream{file_name.GetString()} {
    if (this->IsFail() || this->IsBad()) {
      std::cerr << "R/W or logical error while opening '" << file_name.GetString() << "'." << std::endl;
      exit(1);
    }
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

