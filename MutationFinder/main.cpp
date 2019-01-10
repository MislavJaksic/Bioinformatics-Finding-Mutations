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



  for (auto& read : reads) {
    read.Transform(settings.character_to_digit_pairs);
    read.ExtractMinimizers(settings.kmer_length, settings.minimizer_window_length);
    if (reference_genome.IsReverseAlignment(read)) {
      read.Reverse();
      read.ExtractMinimizers(settings.kmer_length, settings.minimizer_window_length);
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
