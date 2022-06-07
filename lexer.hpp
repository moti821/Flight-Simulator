#pragma once
#include <iostream>
#include <vector>
#include <string>

class Lexer
{
public:
    static Lexer* get_instance();
    void opneInstructionsFile(std::string file_path);
    std::vector<std::string> getLine(int i);
    const std::vector<std::vector<std::string>>& getAllLines();
    void split_string(std::string const &str, const char delimiter,
                      std::vector<std::string> &vec_line);

private:
    static Lexer* instance;
    Lexer(){};
    static std::vector<std::vector<std::string>> all_lines;

};
