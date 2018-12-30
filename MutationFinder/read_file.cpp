#include "read_file.h"



std::vector<SequenceWrapper> ReadFastaFile(StringWrapper &file_name) {
  std::ifstream init_stream = CreateInputStream(file_name);
  InputFileStreamWrapper input_stream{init_stream};

  std::vector<SequenceWrapper> sequences = LoadSequences(input_stream);
  input_stream.Close();

  return sequences;
}

std::ifstream CreateInputStream(StringWrapper &file_name) {
  std::ifstream input_stream(file_name.Get());

  if (input_stream.good()) {
    return input_stream;
  }

  std::cerr << "R/W, EOF or logical error while opening '" << file_name.Get() << "'." << std::endl;
  return input_stream;
}

std::vector<SequenceWrapper> LoadSequences(InputFileStreamWrapper &input_stream) {
  std::vector<SequenceWrapper> sequences;

  std::vector<char> init_description;
  VectorWrapper description{init_description};
  std::vector<char> init_sequence;
  VectorWrapper sequence{init_sequence};

  std::string init_string;
  StringWrapper line{init_string};
  bool is_sequence_full = false;

  while (input_stream.IsAllFlagsGood()) {
    line = input_stream.ReadLine();

    if (line.IsFull()) {
      if (line.IsBeginsWithGreaterThen()) {

        if (is_sequence_full) {
          AddDescriptionAndSequenceToSequences(description, sequence, sequences);

          description.Clear();
          sequence.Clear();
          is_sequence_full = false;
        }
        description.Append(line);

      } else {
        sequence.Append(line);
        is_sequence_full = true;
      }
    }
  }

  AddDescriptionAndSequenceToSequences(description, sequence, sequences);

  return sequences;
}

void AddDescriptionAndSequenceToSequences(VectorWrapper &description, VectorWrapper &sequence, std::vector<SequenceWrapper> &sequences) {
  std::map<KmerKey, std::vector<unsigned int>> init_map;
  MapWrapper<KmerKey, std::vector<unsigned int>> init_index{init_map};
  KmerIndex init_minimizer_index{init_index};

  std::vector<KmerTriple> init_minimizers;

  SequenceWrapper wrapper{description, sequence, init_minimizers, init_minimizer_index};
  sequences.push_back(wrapper);
}
