#pragma once
#include <iostream>
#include <vector>
#include <string>

class Lexer
{
public:
    static Lexer* get_instance();
    void open_instructions_file(std::string file_path);
    std::vector<std::string> get_line(int num_line);
    int get_size();
    void split_string(std::string const &str, const char delimiter,
                      std::vector<std::string> &vec_line);

private:
    static Lexer* instance;
    Lexer(){};
    std::string delete_space(std::string);
    static std::vector<std::vector<std::string>> all_lines;

};
