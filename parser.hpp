#pragma once
#include <unordered_map>
#include "command.hpp"
#include "lexer.hpp"

class Parser
{
public:
    Parser();
    ~Parser();

    void parse(const std::string &path);
    Command *get_command(const std::string &name_command);
    static std::vector<int> vec_lines_to_while;

private:
    void create_vec_line(int num_line_to_start, Lexer *lex);
    std::unordered_map<std::string, Command *> commands;
};