#include "main.h"



int main(void) {
  String file_name{"lambda.fasta"};

  std::vector<Sequence> sequences_A = LoadSequencesFromFile(file_name);
  Sequence sequence_A = sequences_A[0];

  file_name = "lambda_simulated_reads.fasta";
  std::vector<Sequence> sequences_B = LoadSequencesFromFile(file_name);

  sequence_A.Transform();
  sequence_A.IndexMinimizers(20, 20);
  //std::cout << sequence_A << std::endl;



  for (auto& element : sequences_B) {
    element.Transform();
    element.ExtractMinimizers(20, 20);
    //std::cout << element << std::endl;
  }

  int found = 0;
  SequenceMapper mapper{};
  std::map<char, char> reverse_transformer = {{'1', 'A'}, {'2', 'T'}, {'3', 'G'}, {'0', 'C'}};

  for (Sequence& sequence_B : sequences_B) {
    std::cout << sequence_B.getDescription() << std::endl;
    std::vector<unsigned int> positions = mapper.getMatchingPositions(sequence_A, sequence_B);
    found += (positions.size() > 0) ? 1 : 0;

    if (positions.size() > 0) {
        std::cout << "Genom = " << positions[0] << ", Fragmet = " << positions[1] << ", Reverse = " << (positions[2] == 1) << std::endl;

        for (int i=-15; i<=35; i++) {
            int pos_A = positions[0] + i;
            if (i == 0 || i == 19) {
                std::cout << " ";
            }
            if (pos_A < 0 || pos_A >= (int)sequence_A.getSequence().Length()) {
                std::cout << "-";
            } else {
                std::cout << reverse_transformer[sequence_A.getSequence()[pos_A]];
            }
        }
        std::cout << std::endl;

        for (int i=-15; i<=35; i++) {
            int pos_B = positions[1] + i;
            if (i == 0 || i == 19) {
                std::cout << " ";
            }
            if (pos_B < 0 || pos_B >= (int)sequence_B.getSequence().Length()) {
                std::cout << "-";
            } else {
                std::cout << reverse_transformer[sequence_B.getSequence()[pos_B]];
            }
        }
        std::cout << std::endl;
    }
    std::cout << std::endl;
  }

  std::cout << "Found " << found << ", out of: " << sequences_B.size() << std::endl;

  return 0;
}
