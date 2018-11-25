#include "read_file.h"

FastaWrapper ReadFastaFile(String &file_name) {
  InputFileStream input_stream = CreateInputStream(file_name);

  FastaWrapper wrapper = LoadFasta(input_stream);

  Close(input_stream);
  return wrapper;
}

FastaWrapper LoadFasta(InputFileStream &input_stream) {
  CharVector description;
  CharVector sequence;

  while (IsAllFlagsGood(input_stream)) {
    String line = ReadLine(input_stream);

    if (IsFull(line)) {
      if (IsBeginsWithGreaterThen(line)) {
        //std::cout << "Intro: " << line << std::endl;
        description = AppendStringToVector(line, description);
      } else {
        //std::cout << "Genome: " << line << std::endl;
        sequence = AppendStringToVector(line, sequence);
      }
    }
  }

  FastaWrapper wrapper{description, sequence};

  return wrapper;
}
