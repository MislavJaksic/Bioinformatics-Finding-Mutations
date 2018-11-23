//Header guard start
#ifndef READ_FASTA_FILE
#define READ_FASTA_FILE

//Includes

//Declarations
std::ifstream& CreateInputStream(std::string &file_name);
bool IsAllFlagsGood(std::ifstream &stream);

std::vector<char>& StoreFASTA(std::ifstream &input_stream);

std::string& ReadLine(std::ifstream &stream);
bool IsEmpty(std::string &string);
bool IsBeginsWithGreaterThen(std::string &string);

//Header guard end
#endif
