//Header guard start
#ifndef READ_FILE
#define READ_FILE

//Aliases
#include "type_aliases.h"

//Includes
#include "standard_include.h"
#include "fasta_wrapper.h"
#include "stream_helper.h"
#include "string_helper.h"
#include "vector_helper.h"

//Declarations
FastaWrapper ReadFastaFile(String &file_name);
FastaWrapper LoadFasta(InputFileStream &input_stream);

//Header guard end
#endif
