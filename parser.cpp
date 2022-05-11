#include "parser.hpp"

Parser::Parser()
{
    commands["openDataServer"] = new OpenServerCommand;
    commands["connect"] = new ConnectCommand;
    commands["var"] = new VarCommand;
}

Command *Parser::parse(std::vector<std::string> &line)
{
    Command *next_command = commands[line[0]];
    return next_command;
};
