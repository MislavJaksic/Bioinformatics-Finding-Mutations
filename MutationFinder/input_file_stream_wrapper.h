#ifndef INPUT_FILE_STREAM_WRAPPER
#define INPUT_FILE_STREAM_WRAPPER

//Includes
#include "standard_include.h"
#include "string_wrapper.h"



//Declarations
class InputFileStreamWrapper {
private:
  std::ifstream &stream;

public:
  InputFileStreamWrapper(std::ifstream &stream) :
    stream(stream) {
  }

  StringWrapper ReadLine() {
    std::string line;
    std::getline(this->stream, line);
    StringWrapper wrapper{line};

    return line;
  }



  bool IsAllFlagsGood() {
    if (this->stream.good()) {
      return true;
    }
    return false;
  }



  void ResetFlags() {
    this->stream.clear();
  }

  void Close() {
    this->stream.close();
  }
};

#endif // INPUT_FILE_STREAM_WRAPPER
