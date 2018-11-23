#include "main.h"

void ReadFASTAFile(std::string &file_name)
{
    std::ifstream &input_stream = CreateInputStream(file_name);

    StoreFASTA(input_stream);
}

std::ifstream& CreateInputStream(std::string &file_name)
{
    static std::ifstream input_stream(file_name);
    if (IsAllFlagsGood(input_stream))
    {
        return input_stream;
    }
    std::cerr << "Error opening file '" << file_name << "'." << std::endl;
    return input_stream;
}

bool IsAllFlagsGood(std::ifstream &stream)
{
    if(stream.good())
    {
        return true;
    }
    return false;
}



std::vector<char>& StoreFASTA(std::ifstream &input_stream)
{
    //std::string line;
    std::string name;
    std::string content;
    while(IsAllFlagsGood(input_stream))
    {
        std::string &line = ReadLine(input_stream);

        if(IsEmpty(line) || IsBeginsWithGreaterThen(line))
        {
            if( !IsEmpty(name) )  // Print out what we read from the last entry
            {
                std::cout << name << " : " << content << std::endl;
                name.clear();
            }
            if( !IsEmpty(line) )
            {
                name = line.substr(1);
            }
            content.clear();
        }
        else if(!IsEmpty(name))
        {
            if(line.find(' ') != std::string::npos)  // Invalid sequence--no spaces allowed
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
    if( !IsEmpty(name) )  // Print out what we read from the last entry
    {
        std::cout << name << " : " << content << std::endl;
    }

    static std::vector<char> dummy_genome{'A', 'T', 'C', 'G'};

    return dummy_genome;
}



std::string& ReadLine(std::ifstream &stream)
{
    static std::string line;
    std::getline(stream, line);

    return line;
}

bool IsEmpty(std::string &string)
{
    if(string.empty())
    {
        return true;
    }
    return false;
}

bool IsBeginsWithGreaterThen(std::string &string)
{
    if(string[0] == '>')
    {
        return true;
    }
    return false;
}
