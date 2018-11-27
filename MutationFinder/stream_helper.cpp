#include "stream_helper.h"

std::ifstream CreateInputStream(StringWrapper &file_name) {
  std::ifstream input_stream(file_name.Get());

  if (input_stream.good()) {
    return input_stream;
  }

  std::cerr << "R/W, EOF or logical error while opening '" << file_name.Get() << "'." << std::endl;
  return input_stream;
}
