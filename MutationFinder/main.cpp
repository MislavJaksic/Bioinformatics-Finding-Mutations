#include "main.h"



int main(void) {
  String file_name{"lambda.fasta"};

  std::vector<Sequence> sequences_A = LoadSequencesFromFile(file_name);
  Sequence sequence_A = sequences_A[0];

  file_name = "lambda_simulated_reads.fasta";
  std::vector<Sequence> sequences_B = LoadSequencesFromFile(file_name);

  sequence_A.Transform();
  sequence_A.IndexMinimizers(20, 40);
  //std::cout << sequence_A << std::endl;



  for (auto& element : sequences_B) {
    element.Transform();
    element.ExtractMinimizers(20, 40);
    //std::cout << element << std::endl;
  }

  int found = 0;
  SequenceMapper mapper{};
  std::map<char, char> reverse_transformer = {{'1', 'A'}, {'2', 'T'}, {'3', 'G'}, {'0', 'C'}};

  std::map<int, std::vector<mutation>> mutation_map{};

  for (Sequence& sequence_B : sequences_B) {
    std::cout << sequence_B.getDescription() << std::endl;
    //std::vector<unsigned int> positions = mapper.getMatchingPositions(sequence_A, sequence_B);

    /*
    if (points.size() > 1) {
        std::cout << "minimizer_number = " << sequence_B.getMinimizers().size() << std::endl;
        point k_reverse = points[0];
        std::cout << "k = " << k_reverse.x << ", Reverse = " << k_reverse.y << std::endl;

        for (int m = 1; m < (int)points.size(); m++) {
            std::cout << "position_A = " << points[m].x << "; position_B = " << points[m].y << std::endl;
            for (int i=-15; i<=35; i++) {
                int pos_A = points[m].x + i;
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
                int pos_B = points[m].y + i;
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
            std::cout << std::endl;
        }
    }
    */

    std::list<mutation> mutations = mapper.getMutations(sequence_A, sequence_B);

    /*
    for (auto& mut : mutations) {
        std::cout << mut.mutation_character << "," << mut.position << "," << mut.nucleobase << std::endl;
    }
    */

    found += (mutations.size() > 1) ? 1 : 0;
    int mut_found = mutations.size();
    int size_B = sequence_B.getSequence().Length();

    std::cout << "found = " << found;
    std::cout << ", sequence_size_B = " << size_B << ", mutations_found = " << mut_found << ", mutation_statistic = " <<
        ((double)mut_found) / size_B << std::endl;

    std::cout << std::endl;
  }

  std::cout << "Found " << found << ", out of: " << sequences_B.size() << std::endl;

  return 0;
}
