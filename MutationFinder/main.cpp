#include "main.h"

int main(void) {
  std::string init_string = "ecoli.fasta";
  StringWrapper file_name{init_string};
  SequenceWrapper wrapper_A = ReadFastaFile(file_name);

  init_string = "sample_B.fasta";
  file_name.Set(init_string);
  SequenceWrapper wrapper_B = ReadFastaFile(file_name);

  wrapper_A.Print();
  wrapper_B.Print();

  MapWrapper<char, int> letters_A = wrapper_A.CountSequenceValues();
  letters_A.Print();
  MapWrapper<char, int> letters_B = wrapper_B.CountSequenceValues();
  letters_B.Print();


  std::map<char, char> init_map;
  MapWrapper<char, char> letter_digit{init_map};
  letter_digit.Set('A', '1');
  letter_digit.Set('T', '2');
  letter_digit.Set('C', '0');
  letter_digit.Set('G', '3');

  wrapper_A.TransformSequence(letter_digit);
  wrapper_A.Print();

  wrapper_A.ExtractMinimizerKmersOfLengthInWindow(3, 5);
  //wrapper_A.PrintMinimizers();

  return 0;
}
