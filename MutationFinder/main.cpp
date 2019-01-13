/*
Author: Mislav Jaksic
*/

#include "main.h"



int main(int argc, char **argv) {
  CLI::App app{"Mutation finder"};

  unsigned int kmer_length;
  unsigned int minimizer_window_length;

  std::vector<std::string> character_to_digit_pairs;
  std::vector<std::string> complement_pairs;

  std::string reference_genome_file_name;
  std::string reads_file_name;

  app.add_option("-k, --kmer_length", kmer_length, "K-mer length");
  app.add_option("-l, --minimizer_window_length", minimizer_window_length, "K-mer minimizer window length");

  app.add_option("-n, --character_to_digit_pairs", character_to_digit_pairs, "'char, digit..char, digit' pairs which establish total character order");
  app.add_option("-c, --complement_pairs", complement_pairs, "'char,char..char,char' complement pairs, such as DNA nucleobases");

  app.add_option("-g, --reference_genome_file_name", reference_genome_file_name, "Reference sequence FASTA file name");
  app.add_option("-r, --reads_file_name", reads_file_name, "Sequence reads FASTA file name");

  app.set_config("--config", "settings.ini", "Read an .ini settings file", true);

  CLI11_PARSE(app, argc, argv);
  Settings settings = ConstructSettings(kmer_length, minimizer_window_length, character_to_digit_pairs, complement_pairs, reference_genome_file_name, reads_file_name);



  String file_name{settings.reference_genome_file_name};
  std::vector<Sequence> single_sequence = LoadSequencesFromFile(file_name);
  Sequence reference_genome = single_sequence[0];

  file_name = settings.reads_file_name;
  std::vector<Sequence> reads = LoadSequencesFromFile(file_name);

  reference_genome.Transform(settings.character_to_digit_pairs);
  reference_genome.IndexMinimizers(settings.kmer_length, settings.minimizer_window_length);
  std::cout << reference_genome << std::endl;

  /*
  === ===
  Author: Josip Kasap
  */


  int found = 0;
  double mut_stat{0.0};
  SequenceMapper mapper{};

  std::map<unsigned int, std::vector<mutation_count>> mutation_map{};
  std::map<unsigned int, int> count_map{};

  /*
  === ===
  Author: Mislav Jaksic
  */

  for (Sequence& read : reads) {
    read.Transform(settings.character_to_digit_pairs);
    read.ExtractMinimizers(settings.kmer_length, settings.minimizer_window_length);
    if (reference_genome.IsReverseAlignment(read)) {
      read.Reverse();
      read.ExtractMinimizers(settings.kmer_length, settings.minimizer_window_length);
    }

    /*
    === ===
    Author: Josip Kasap
    */

    std::cout << read.GetDescription() << std::endl;
    std::vector<point> points = mapper.getAllMatchingPositions(reference_genome, read);

    std::cout << "Shared positions = " << ((points.size() <= 1) ? 0 : points.size() - 1) << std::endl;
    if (points.size() < 2)
      continue;

    unsigned int start_A = points[1].x - points[1].y > 0 ? points[1].x - points[1].y : 0;
    unsigned int end_A = points[points.size() - 1].x + read.Length() - points[points.size() - 1].y - 1;
    end_A = end_A < reference_genome.Length() ? end_A : reference_genome.Length() - 1;

    std::list<mutation> mutations = mapper.getMutations(reference_genome, read);

    int size_B = read.Length();
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
        count_map.insert(std::pair<unsigned int, int>(i, 1));
      }
    }

    for (auto& mut : mutations) {
      if (mutation_map.count(mut.position) < 1) {
        std::vector<mutation_count> mutts{};
        mutation_map.insert(std::pair<int, std::vector<mutation_count>>(mut.position, mutts));
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
    read.ClearMinimizers();
  }

  std::cout << "Found = " << found << ", out of: " << reads.size() << std::endl;

  mut_stat = mut_stat / found;
  std::cout << "Mutation statistic average = " << mut_stat << std::endl;

  std::vector<mutation_count> mut_vector{};

  for (int i = 0; i < (int)reference_genome.Length(); i++) {
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
      count_val = count_val / 2;
      if (count_val % 2 == 1)
        count_val += 1;
    } else {
      count_val = count_val / 2;
    }


    if (max_mut_count->number >= count_val && max_mut_count->number >= 2) {
      mut_vector.push_back(*max_mut_count);
    }
  }

  std::ofstream myfile;
  myfile.open("out.csv", std::ios::out | std::ios::binary);

  for (mutation_count& mut_count : mut_vector) {
    std::cout << mut_count.mut.mutation_character << "," << mut_count.mut.position << "," << mut_count.mut.nucleobase <<
              "   \t number = " << mut_count.number << std::endl;

    myfile << mut_count.mut.mutation_character << "," << mut_count.mut.position << "," << mut_count.mut.nucleobase << std::endl;
  }

  myfile.close();

  return 0;
}

/*
=== ===
*/
