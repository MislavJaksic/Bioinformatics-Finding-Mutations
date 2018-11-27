#include "read_file.h"

SequenceWrapper ReadFastaFile(StringWrapper &file_name) {
  std::ifstream stream = CreateInputStream(file_name);
  InputFileStreamWrapper input_stream{stream};

  SequenceWrapper wrapper = LoadFasta(input_stream);

  input_stream.Close();
  return wrapper;
}

SequenceWrapper LoadFasta(InputFileStreamWrapper &input_stream) {
  std::vector<char> description;
  std::vector<char> sequence;

  while (input_stream.IsAllFlagsGood()) {
    StringWrapper line = input_stream.ReadLine();

    if (line.IsFull()) {
      if (line.IsBeginsWithGreaterThen()) {
        description = AppendStringWrapperToVector(line, description);
      } else {
        sequence = AppendStringWrapperToVector(line, sequence);
      }
    }
  }

  SequenceWrapper wrapper{description, sequence};

  return wrapper;
}
