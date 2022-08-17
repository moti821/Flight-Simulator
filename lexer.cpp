#include <fstream>
#include "lexer.hpp"
#include "tools.hpp"

std::vector<std::vector<std::string>> Lexer::all_lines;

void Lexer::open_instructions_file(std::string file_path)
{

    std::string string_line;
    std::fstream fs;

    fs.open(file_path, std::fstream::in);

    const char delim = ' ';
    while (std::getline(fs, string_line))
    {

        std::vector<std::string> vec_line;

        split_string(string_line, delim, vec_line);

        if (!std::isalpha(vec_line[0][0]) && vec_line[0][0] != '}')
            vec_line[0] = delete_space(vec_line[0]);

        all_lines.push_back(vec_line);
    };
    fs.close();

    // print_all_vectors();

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
    while (!std::isalpha(to_fix[0]))
    {
        to_fix.erase(0, 1);
    }
    return to_fix;
}

void Lexer::print_all_vectors()
{
    for (int i = 0; i < all_lines.size(); i++)
    {
        for (int j = 0; j < all_lines[i].size(); j++)
        {
            std::cout << all_lines[i][j] << " ";
        }
        std::cout << std::endl;
    }
}
