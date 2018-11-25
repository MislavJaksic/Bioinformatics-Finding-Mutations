#include "stream_helper.h"

InputFileStream CreateInputStream(String &file_name) {
  InputFileStream input_stream(file_name);
  if (IsAllFlagsGood(input_stream)) {
    return input_stream;
  }

  std::cerr << "R/W, EOF or logical error while opening '" << file_name << "'." << std::endl;
  return input_stream;
}



String ReadLine(InputFileStream &stream) {
  String line;
  std::getline(stream, line);

  return line;
}



bool IsAllFlagsGood(InputFileStream &stream) {
  if (stream.good()) {
    return true;
  }
  return false;
}



void Close(InputFileStream &stream) {
  stream.close();
}

void ResetFlags(InputFileStream &stream) {
  stream.clear();
}
