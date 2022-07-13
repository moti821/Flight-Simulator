#include <fstream>
#include <sstream>
#include "lexer.hpp"

std::vector<std::vector<std::string>> Lexer::all_lines;


Lexer* Lexer::instance = 0;

Lexer* Lexer::get_instance()
{
    if(instance == 0)
    {
        Lexer* instance = new Lexer;
    }
    return instance;
}


void Lexer::opne_instructions_file(std::string file_path)
{

    std::string string_line;
    std::fstream fs;

    fs.open(file_path, std::fstream::in);

    while (std::getline(fs, string_line))
    {

        std::vector<std::string> vec_line;
        const char delim = ' ';

        split_string(string_line, delim, vec_line);

        if(!std::isalpha(vec_line[0][0]) && vec_line[0][0] != '}')
        vec_line[0] = delete_space(vec_line[0]);

        all_lines.push_back(vec_line);

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
                         std::vector<std::string> &vec_of_strings)
{
    std::string strings_to_vector;

    std::stringstream string_stream(str);

    while (std::getline(string_stream, strings_to_vector, delim))
    {
        vec_of_strings.push_back(strings_to_vector);
    }
    return;
}

std::vector<std::string> Lexer::get_line(int i)
{
    if (all_lines[i].size() < 1)
    {
        std::cout << "The line not exist" << std::endl;
    }
    return all_lines[i];
}

int Lexer::get_size()
{
    if (all_lines.size() < 1)
    {
        std::cout << "The data not exzist" << std::endl;
    };
    return all_lines.size();
}

std::string Lexer::delete_space(std::string to_fix)
{
        while(!std::isalpha(to_fix[0]))
        {
            to_fix.erase(0,1);
        }
        return to_fix; 
}
