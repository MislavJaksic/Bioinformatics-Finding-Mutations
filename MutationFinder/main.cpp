#include "main.h"



int main(void) {
  String file_name{"lambda.fasta"};

  std::vector<Sequence> single_sequence = LoadSequencesFromFile(file_name);
  Sequence reference_genome = single_sequence[0];

  file_name = "lambda_simulated_reads.fasta";
  std::vector<Sequence> reads = LoadSequencesFromFile(file_name);

  reference_genome.Transform();
  reference_genome.IndexMinimizers(10, 20);
  std::cout << reference_genome << std::endl;



  for (auto& read : reads) {
    read.Transform();
    read.ExtractMinimizers(10, 20);
    //std::cout << read << std::endl;
  }

  Sequence read{reads[0]};
  std::cout << read.GetDescription() << std::endl;
  for (auto& minimizer : read.minimizers) {
    KmerKey true_key{minimizer.GetKey().GetKmer(), false};
    KmerKey reverse_key{minimizer.GetKey().GetKmer(), true};

    std::vector<unsigned int> true_positions{reference_genome.minimizer_index[true_key]};
    std::vector<unsigned int> reverse_positions{reference_genome.minimizer_index[reverse_key]};

    std::cout << true_key;
    for (auto& position : true_positions) {
        std::cout << position << ",";
    }
    std::cout << std::endl;

    std::cout << reverse_key;
    for (auto& position : reverse_positions) {
        std::cout << position << ",";
    }
    std::cout << std::endl;
  }

//  for (auto& element : reference_genome.minimizer_index[key]) {
//    std::cout << element << ",";
//  }

  //std::cout << "Sleeping... Zzzzz..." << std::endl;
  //std::this_thread::sleep_for(std::chrono::milliseconds(10000));

  return 0;
}
