#include "main.h"

void read_fasta_file(std::string file_name)
{
    std::ifstream input(file_name);
    if(!input.good())
    {
        std::cerr << "Error opening '" << file_name << "'. Did not open the file." << std::endl;
    }

    std::string line, name, content;
    while( std::getline( input, line ).good() )
    {
        if( line.empty() || line[0] == '>' )  // Identifier marker
        {
            if( !name.empty() )  // Print out what we read from the last entry
            {
                std::cout << name << " : " << content << std::endl;
                name.clear();
            }
            if( !line.empty() )
            {
                name = line.substr(1);
            }
            content.clear();
        }
        else if( !name.empty() )
        {
            if( line.find(' ') != std::string::npos )  // Invalid sequence--no spaces allowed
            {
                name.clear();
                content.clear();
            }
            else
            {
                content += line;
            }
        }
    }
    if( !name.empty() )  // Print out what we read from the last entry
    {
        std::cout << name << " : " << content << std::endl;
    }
}
