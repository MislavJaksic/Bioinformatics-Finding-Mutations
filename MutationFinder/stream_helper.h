#ifndef STREAM_HELPER
#define STREAM_HELPER

//Aliases
#include "type_aliases.h"

//Includes
#include "standard_include.h"

//Declarations
InputFileStream CreateInputStream(String &file_name);

String ReadLine(InputFileStream &stream);

bool IsAllFlagsGood(InputFileStream &stream);

void Close(InputFileStream &stream);
void ResetFlags(InputFileStream &stream);

#endif // STREAM_HELPER
