#pragma once
#include <unordered_map>
#include "command.hpp"

class Parser
{
public:
    Parser();

    Command* parse(std::vector<std::string>&);

private:
    std::unordered_map<std::string, Command *> commands;
    // std::unordered_map<std::string, std::string> variable;
};