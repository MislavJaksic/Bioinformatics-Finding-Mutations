#include "read_file.h"

SequenceWrapper ReadFastaFile(StringWrapper &file_name) {
  std::ifstream init_stream = CreateInputStream(file_name);
  InputFileStreamWrapper input_stream{init_stream};

  SequenceWrapper wrapper = LoadFasta(input_stream);
  input_stream.Close();

  return wrapper;
}

SequenceWrapper LoadFasta(InputFileStreamWrapper &input_stream) {
  std::vector<char> init_description;
  std::vector<char> init_sequence;
  VectorWrapper description{init_description};
  VectorWrapper sequence{init_sequence};

  std::string init_string;
  StringWrapper line{init_string};

  while (input_stream.IsAllFlagsGood()) {
    line = input_stream.ReadLine();

    if (line.IsFull()) {
      if (line.IsBeginsWithGreaterThen()) {
        description.Append(line);
      } else {
        sequence.Append(line);
      }
    }
  }

  std::vector<KmerTriple> init_minimizers;
  SequenceWrapper wrapper{description, sequence, init_minimizers};

  return wrapper;
}
