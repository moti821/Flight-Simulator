#pragma once
#include <unordered_map>
#include "command.hpp"

class Parser
{
public:
    Parser();

    Command* parse(std::vector<std::string>&);
    std::string delete_space(std::string);
    std::string find_word_convert_to_value(std::string str_line);

private:
    std::unordered_map <std::string, Command *> commands;
};