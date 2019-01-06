#include "main.h"



int main(void) {
  String file_name{"ecoli.fasta"};

  std::vector<Sequence> sequences_A = LoadSequencesFromFile(file_name);
  Sequence sequence_A = sequences_A[0];

  file_name = "ecoli_simulated_reads.fasta";
  std::vector<Sequence> sequences_B = LoadSequencesFromFile(file_name);

  sequence_A.Transform();
  sequence_A.IndexMinimizers(20, 20);
  std::cout << sequence_A << std::endl;



  for (auto& element : sequences_B) {
    element.Transform();
    //element.IndexMinimizers(20, 20);
    //std::cout << element << std::endl;
  }

  Kmer kmer{'0','2','0'};
  KmerKey key{kmer, 1};
//  for (auto& element : sequence_A.minimizer_index[key]) {
//    std::cout << element << ",";
//  }

  //std::cout << "Sleeping... Zzzzz..." << std::endl;
  //std::this_thread::sleep_for(std::chrono::milliseconds(10000));

  return 0;
}
