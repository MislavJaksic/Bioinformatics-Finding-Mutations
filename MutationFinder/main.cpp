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

  return 0;
}
