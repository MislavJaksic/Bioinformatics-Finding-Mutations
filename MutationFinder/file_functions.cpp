#include "file_functions.h"



std::vector<Sequence> LoadSequencesFromFile(String &file_name) {
  FileReader reader{file_name};

  std::vector<Sequence> sequences = ReadFasta(reader);

  reader.Close();
  return sequences;
}

std::vector<Sequence> ReadFasta(FileReader &reader) {
  std::vector<Sequence> sequences;

  String fasta_description;
  CharVector fasta_sequence;

  bool is_sequence_not_empty = false;
  String line;

  while (reader.IsFlagsUnset()) {
    line = reader.ReadLine();
    if (line.IsEmpty()) {
      continue;
    }

    if (line.IsCharAt('>', 0)) {
      if (is_sequence_not_empty) {
        Sequence sequence{fasta_description, fasta_sequence};
        sequences.push_back(sequence);

        fasta_description.Clear();
        fasta_sequence.Clear();
        is_sequence_not_empty = false;
      }
      fasta_description = line;

    } else {
      fasta_sequence.Append(line);
      is_sequence_not_empty = true;
    }
  }
  Sequence sequence{fasta_description, fasta_sequence};
  sequences.push_back(sequence);

  return sequences;
}
