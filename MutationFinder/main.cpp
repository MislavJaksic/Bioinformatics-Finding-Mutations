#include "main.h"

int main(void) {

  String file_name = "ecoli_iai39.fasta";
  FastaWrapper wrapper_A = ReadFastaFile(file_name);

  file_name = "ecoli_o157.fasta";
  FastaWrapper wrapper_B = ReadFastaFile(file_name);

  wrapper_A.Print();
  wrapper_B.Print();

  std::map<char, int> letters = wrapper_A.CountOccurrences();
  Print(letters);

  return 0;
}
