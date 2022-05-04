#pragma once
#include "lexer.hpp"
#include "command.hpp"
#include "server.hpp"
#include "client.hpp"

class Parser
{
public:

    Parser();

    void pars();

private:
    std::unordered_map<std::string,Command*> commands;

    void create_h_map();

    void runner(Command* command);
};