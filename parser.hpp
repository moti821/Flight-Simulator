#pragma once
#include <unordered_map>
#include "command.hpp"

class Parser
{
public:
    Parser();

    Command* parse(std::vector<std::string>&);
    std::string delete_space(std::string);

private:
    std::unordered_map <std::string, Command *> commands;
};