//Header guard start
#ifndef FILE_FUNCTIONS
#define FILE_FUNCTIONS

//Includes
#include <vector>
#include <string>

#include "FileReader.h"
#include "Sequence.h"
#include "String.h"

//Declarations
std::vector<Sequence> LoadSequencesFromFile(String &file_name);
std::vector<Sequence> ReadFasta(FileReader &reader);

//Header guard end
#endif
