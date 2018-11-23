#include "main.h"

int main(void)
{
    std::cout << "Hello world!" << std::endl;
    std::string file_name = "sample.fasta";
    ReadFASTAFile(file_name);
    return 0;
}
