#include "FileReader.h"



String FileReader::ReadLine() {
  std::string line;
  std::getline(this->stream, line);

  return line;
}



bool FileReader::IsFlagsUnset() {
  if (this->stream.good()) {
    return true;
  }
  return false;
}

bool FileReader::IsEOF() {
  if (this->stream.eof()) {
    return true;
  }
  return false;
}

bool FileReader::IsFail() {
  if (this->stream.fail()) {
    return true;
  }
  return false;
}

bool FileReader::IsBad() {
  if (this->stream.bad()) {
    return true;
  }
  return false;
}

void FileReader::ResetFlags() {
  this->stream.clear();
}



void FileReader::HandleFailError(const String &file_name) {
  if (this->IsFail()) {
    std::cerr << "Read/write error while opening '" << file_name.GetString() << "'." << std::endl;
    this->Close();
  }
}

void FileReader::HandleBadError(const String &file_name) {
  if (this->IsBad()) {
    std::cerr << "Logical error while opening '" << file_name.GetString() << "'." << std::endl;
    this->Close();
  }
}

void FileReader::Close() {
  this->stream.close();
}
