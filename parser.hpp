#pragma once
#include <unordered_map>
#include "lexer.hpp"
#include "command.hpp"

class Parser
{
public:
    Parser();

    void pars();

private:
    std::unordered_map<std::string, Command *> commands;

    void create_h_map();

    void runner(Command *command, std::vector<std::string> comman);
};