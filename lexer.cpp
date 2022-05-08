#include <fstream>
#include <sstream>
#include "lexer.hpp"

void Lexer::opneInstructionsFile(std::string file_path)
{

    std::string string_line;
    std::fstream fs;

    fs.open(file_path, std::fstream::in);

    while (std::getline(fs, string_line))
    {

        std::vector<std::string> vec_line;
        const char delim = ' ';

        split_string(string_line, delim, vec_line);

        all_lines.push_back(vec_line);

        if (string_line == "-1")
        {
            break;
        }
    };
    fs.close();

    // for( int i=0 ; i < all_lines.size() ; i++ ){
    //     for( int j=0 ; j < all_lines[i].size() ; j++){
    //         std::cout << all_lines[i][j] << " ";
    //     }
    //     std::cout << std::endl;
    // }
    return;
};

void Lexer::split_string(std::string const &str, const char delim,
                         std::vector<std::string> &vec_line)
{
    std::string strings_line;

    // construct a stream from the string
    std::stringstream string_stream(str);

    while (std::getline(string_stream, strings_line, delim))
    {
        vec_line.push_back(strings_line);
    }
    return;
}

std::vector<std::string> Lexer::getLine(int i)
{
    if (all_lines[i].size() < 1)
    {
        std::cout << "The line not exist" << std::endl;
    }
    return all_lines[i];
}

std::vector<std::vector<std::string>> Lexer::getAllLines()
{
    if (all_lines.size() < 1)
    {
        std::cout << "The data not exzist" << std::endl;
    };
    return all_lines;
}
