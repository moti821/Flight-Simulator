#pragma once
#include <vector>
#include <string>

class Lexer
{
public:
    void open_instructions_file(const std::string &file_path);
    std::vector<std::string> get_line(int num_line);
    size_t get_size();

private:
    std::string delete_space(std::string str);
    void print_all_vectors();
    static std::vector<std::vector<std::string>> all_lines;
};
