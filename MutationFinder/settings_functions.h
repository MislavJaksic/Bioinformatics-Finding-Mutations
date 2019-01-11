//Header guard start
#ifndef SETTINGS_FUNCTIONS
#define SETTINGS_FUNCTIONS

//Includes
#include <string>
#include <vector>
#include <map>

#include "CLI11.hpp"

//Declarations
struct Settings {
  unsigned int kmer_length;
  unsigned int minimizer_window_length;

  std::map<char,char> character_to_digit_pairs;
  std::map<char,char> complement_pairs;

  std::string reference_genome_file_name;
  std::string reads_file_name;
};

Settings ConstructSettings(unsigned int kmer_length,
                           unsigned int minimizer_window_length,
                           std::vector<std::string> character_to_digit_pairs,
                           std::vector<std::string> complement_pairs,
                           std::string reference_genome_file_name,
                           std::string reads_file_name);
std::map<char,char> TransformToMap(std::vector<std::string> vector);

//Header guard end
#endif
