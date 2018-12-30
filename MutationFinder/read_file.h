//Header guard start
#ifndef READ_FILE
#define READ_FILE

//Aliases

//Includes
#include "standard_include.h"
#include "sequence_wrapper.h"
#include "input_file_stream_wrapper.h"
#include "string_wrapper.h"
#include "map_wrapper_template.h"
#include "kmer_index.h"
#include "kmer_key.h"


//Declarations
std::vector<SequenceWrapper> ReadFastaFile(StringWrapper &file_name);
std::ifstream CreateInputStream(StringWrapper &file_name);
std::vector<SequenceWrapper> LoadSequences(InputFileStreamWrapper &input_stream);
void AddDescriptionAndSequenceToSequences(VectorWrapper &description, VectorWrapper &sequence, std::vector<SequenceWrapper> &sequences);

//Header guard end
#endif
