#include "main.h"



int main(void) {
  String file_name{"lambda.fasta"};

  std::vector<Sequence> sequences_A = LoadSequencesFromFile(file_name);
  Sequence sequence_A = sequences_A[0];

  file_name = "lambda_simulated_reads.fasta";
  std::vector<Sequence> sequences_B = LoadSequencesFromFile(file_name);
  int k_len{20}, w_len{40};

  sequence_A.Transform();
  sequence_A.IndexMinimizers(k_len, w_len);
  //std::cout << sequence_A << std::endl;

  std::map<char, char> reverse_nucleobase = {{'0', '3'}, {'1', '2'}, {'2', '1'}, {'3', '0'}};

  for (auto& read : sequences_B) {
    read.Transform();
    read.ExtractMinimizers(k_len, w_len);
    if (sequence_A.IsReverseAlignment(read)) {
      read.Reverse();
      //read.Transform(reverse_nucleobase);
      read.ExtractMinimizers(k_len, w_len);
    }
  }

  int found = 0;
  //int counter = -1;
  double mut_stat{0.0};
  SequenceMapper mapper{};
  std::map<char, char> reverse_transformer = {{'1', 'A'}, {'2', 'T'}, {'3', 'G'}, {'0', 'C'}};

  std::map<unsigned int, std::vector<mutation_count>> mutation_map{};
  std::map<unsigned int, int> count_map{};

  //std::cout << "Genome length = " << sequence_A.Length() << std::endl;

  for (Sequence& sequence_B : sequences_B) {
    /*
    counter++;
    if (counter != 15)
        continue;
    */
    std::cout << sequence_B.getDescription() << std::endl;
    std::vector<point> points = mapper.getAllMatchingPositions(sequence_A, sequence_B);
    //std::cout << "minimizer_number = " << sequence_B.getMinimizers().size() << std::endl;
    std::cout << "Shared positions = " << ((points.size() <= 1)? 0 : points.size() - 1) << std::endl;
    if (points.size() < 2)
        continue;

    unsigned int start_A = points[1].x - points[1].y >= 0 ? points[1].x - points[1].y : 0;
    unsigned int end_A = points[points.size() - 1].x + sequence_B.getSequence().Length() - points[points.size() - 1].y - 1;
    end_A = end_A < sequence_A.getSequence().Length() ? end_A : sequence_A.getSequence().Length() - 1;

    /*
    if (points.size() > 1) {
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

    //std::cout << "start_A = " << start_A << ", end_A = " << end_A << std::endl;
    //std::cout << "minimizer_number = " << sequence_B.getMinimizers().size() << std::endl;

    int size_B = sequence_B.getSequence().Length();
    std::cout << "found = " << found << ", sequence_size_B = " << size_B ;

    int mut_found = mutations.size();

    std::cout << ", mutations_found = " << mut_found << ", mutation_statistic = " <<
        ((double)mut_found) / size_B << std::endl;

    double mut_stat_seq = ((double)mut_found) / size_B;

    if (mut_stat_seq > 0.25) {
        std::cout << "Overly big mutation, this read will be dissmissed!" << std::endl << std::endl;
        continue;
    }

    found++;
    mut_stat += mut_stat_seq;

    for (int i = (int)start_A; i <= (int)end_A; i++) {
        if (count_map.count(i) > 0) {
            count_map[i] = count_map[i] + 1;
        } else {
            count_map.insert( std::pair<unsigned int, int>(i, 1) );
        }
    }

    for (auto& mut : mutations) {
        //std::cout << mut.mutation_character << "," << mut.position << "," << mut.nucleobase << std::endl;
        if (mutation_map.count(mut.position) < 1) {
            std::vector<mutation_count> mutts{};
            mutation_map.insert( std::pair<int, std::vector<mutation_count>>(mut.position, mutts) );
        }

        bool is_added = false;
        for (auto& mut_count : mutation_map[mut.position]) {
            if (mut_count.mut == mut) {
                mut_count.number = mut_count.number + 1;
                is_added = true;
                break;
            }
        }

        if (is_added == false) {
            mutation_count mut_count{mut, 1};
            mutation_map[mut.position].push_back(mut_count);
        }
    }

    std::cout << std::endl;
    //return 0;
  }

  std::cout << "Found = " << found << ", out of: " << sequences_B.size() << std::endl;

  mut_stat = mut_stat / found;
  std::cout << "Mutation statistic average = " << mut_stat << std::endl;

  std::vector<mutation_count> mut_vector{};

  for (int i=0; i < (int)sequence_A.getSequence().Length(); i++) {
    if (mutation_map.count((unsigned int)i) < 1)
        continue;
    mutation_count *max_mut_count = &mutation_map[(unsigned int)i][0];
    for (auto& mut_count : mutation_map[(unsigned int)i]) {
        if (mut_count.number > max_mut_count->number) {
            max_mut_count = &mut_count;
        }
    }

    int count_val = count_map[max_mut_count->mut.position];
    if (count_val <= 1)
        continue;
    if (count_val > 5 && count_val < 10) {
        count_val = count_val/2;
        if (count_val % 2 == 1)
            count_val += 1;
    } else {
        count_val = count_val/2;
    }


    if (max_mut_count->number >= count_val && max_mut_count->number >= 2) {
        mut_vector.push_back(*max_mut_count);
        //std::cout << "position = " << max_mut_count->mut.position << ", coverage = " << count_map[max_mut_count->mut.position] << std::endl;
    }
  }

  std::ofstream myfile;
  myfile.open ("out.csv", std::ios::out | std::ios::binary);

  for (mutation_count& mut_count : mut_vector) {
      std::cout << mut_count.mut.mutation_character << "," << mut_count.mut.position << "," << mut_count.mut.nucleobase <<
        "   \t number = " << mut_count.number << std::endl;

    myfile << mut_count.mut.mutation_character << "," << mut_count.mut.position << "," << mut_count.mut.nucleobase << std::endl;
  }

  myfile.close();
  return 0;
}
