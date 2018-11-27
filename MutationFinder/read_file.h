//Header guard start
#ifndef READ_FILE
#define READ_FILE

//Aliases

//Includes
#include "standard_include.h"
#include "sequence_wrapper.h"
#include "input_file_stream_wrapper.h"
#include "string_wrapper.h"
#include "vector_helper.h"
#include "stream_helper.h"

//Declarations
SequenceWrapper ReadFastaFile(StringWrapper &file_name);
SequenceWrapper LoadFasta(InputFileStreamWrapper &input_stream);

//Header guard end
#endif
