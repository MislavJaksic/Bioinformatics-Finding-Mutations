#include "main.h"



int main(int argc, char **argv) {
  CLI::App program{"Mutation finder"};

  unsigned int kmer_length;
  unsigned int minimizer_window_length;
  std::string reference_genome_file_name;
  std::string reads_file_name;

  program.add_option("-k, --kmer_length", kmer_length, "K-mer/minimizer length");
  program.add_option("-l, --minimizer_window_length", minimizer_window_length, "Minimizer window length");
  program.add_option("-g, --reference_genome_file_name", reference_genome_file_name, "Reference genome FASTA file name");
  program.add_option("-r, --reads_file_name", reads_file_name, "Reads FASTA file name");
  program.set_config("--config", "settings.ini", "Read an .ini settings file", true);

  CLI11_PARSE(program, argc, argv);



  String file_name{reference_genome_file_name};
  std::vector<Sequence> single_sequence = LoadSequencesFromFile(file_name);
  Sequence reference_genome = single_sequence[0];

  file_name = reads_file_name;
  std::vector<Sequence> reads = LoadSequencesFromFile(file_name);

  reference_genome.Transform();
  reference_genome.IndexMinimizers(kmer_length, minimizer_window_length);
  std::cout << reference_genome << std::endl;



  for (auto& read : reads) {
    read.Transform();
    read.ExtractMinimizers(kmer_length, minimizer_window_length);
    if (reference_genome.IsReverseAlignment(read)) {
      read.Reverse();
      read.ExtractMinimizers(kmer_length, minimizer_window_length);
    }
    reference_genome.CompareWithSequence(read);
    read.ClearMinimizers();
  }



//  for (auto& element : reference_genome.minimizer_index[key]) {
//    std::cout << element << ",";
//  }

  //std::cout << "Sleeping... Zzzzz..." << std::endl;
  //std::this_thread::sleep_for(std::chrono::milliseconds(10000));

  return 0;
}
