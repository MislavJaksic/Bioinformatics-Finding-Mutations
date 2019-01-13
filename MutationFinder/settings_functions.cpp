/*
Author: Mislav Jaksic
*/

#include "settings_functions.h"

Settings ConstructSettings(unsigned int kmer_length,
                           unsigned int minimizer_window_length,
                           std::vector<std::string> character_to_digit_pairs,
                           std::vector<std::string> complement_pairs,
                           std::string reference_genome_file_name,
                           std::string reads_file_name) {

  std::map<char, char> transformed_character_to_digit_pairs = TransformToMap(character_to_digit_pairs);
  std::map<char, char> transformed_complement_pairs = TransformToMap(complement_pairs);
  Settings settings{kmer_length,
                    minimizer_window_length,
                    transformed_character_to_digit_pairs,
                    transformed_complement_pairs,
                    reference_genome_file_name,
                    reads_file_name};
  return settings;
}

std::map<char, char> TransformToMap(std::vector<std::string> vector) {
  unsigned int length{vector.size()};
  std::map<char, char> map;
  char key;
  char value;

  for (unsigned int i = 0; i < length; i = i + 2) {
    key = vector[i][0];
    value = vector[i + 1][0];
    map[key] = value;
  }
  return map;
}
