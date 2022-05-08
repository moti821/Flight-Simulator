#include <iostream>
#include <vector>
#include <string>
#pragma once

class Lexer
{
public:
    Lexer(){};

    void opneInstructionsFile(std::string file_path);
    std::vector<std::string> getLine(int i);
    std::vector<std::vector<std::string>> getAllLines();

private:
    std::vector<std::vector<std::string>> all_lines;

    void split_string(std::string const &str, const char delim,
                      std::vector<std::string> &vec_line);
};
