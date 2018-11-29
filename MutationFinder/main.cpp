#include "main.h"

int main(void) {
  StringWrapper file_name{"sample_A.fasta"};
  SequenceWrapper wrapper_A = ReadFastaFile(file_name);

  file_name.Set("sample_B.fasta");
  SequenceWrapper wrapper_B = ReadFastaFile(file_name);

  wrapper_A.Print();
  wrapper_B.Print();

  MapWrapper<char, int> letters_A = wrapper_A.CountOccurrences();
  letters_A.Print();

  MapWrapper<char, int> letters_B = wrapper_B.CountOccurrences();
  letters_B.Print();

  std::map<char, char> init_map;
  MapWrapper<char, char> letter_digit{init_map};
  letter_digit.Set('A', '1');
  letter_digit.Set('T', '2');
  letter_digit.Set('C', '0');
  letter_digit.Set('G', '3');

  wrapper_A.TransformSequence(letter_digit);

  wrapper_A.Print();
  wrapper_B.Print();

  return 0;
}
