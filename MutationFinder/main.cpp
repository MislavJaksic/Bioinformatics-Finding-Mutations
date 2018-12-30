#include "main.h"



int main(void) {
  //std::string init_string = "lambda.fasta";
  std::string init_string = "sample_A.fasta";
  StringWrapper file_name{init_string};
  std::vector<SequenceWrapper> sequences_A = ReadFastaFile(file_name);
  SequenceWrapper wrapper_A = sequences_A[0];

  //init_string = "lambda_simulated_reads.fasta";
  init_string = "sample_B.fasta";
  file_name.Set(init_string);
  std::vector<SequenceWrapper> sequences_B = ReadFastaFile(file_name);

  wrapper_A.Print();

  MapWrapper<char, int> letters_A = wrapper_A.CountSequenceValues();
  letters_A.Print();


  std::map<char, char> init_map;
  MapWrapper<char, char> letter_digit{init_map};
  letter_digit.Set('A', '1');
  letter_digit.Set('T', '2');
  letter_digit.Set('C', '0');
  letter_digit.Set('G', '3');

  wrapper_A.TransformSequence(letter_digit);
  wrapper_A.Print();

  wrapper_A.ExtractMinimizerKmersOfLengthInWindow(5, 10);
  wrapper_A.PrintMinimizers();

  wrapper_A.IndexKmerMinimizers();
  wrapper_A.PrintIndex();

  for (auto& element : sequences_B) {
    element.TransformSequence(letter_digit);
    element.ExtractMinimizerKmersOfLengthInWindow(5, 10);
    element.PrintMinimizers();
  }

  return 0;
}
