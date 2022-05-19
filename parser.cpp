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
    if(next_command == (Command*)0x0)
    {
        next_command = new EqualCommand;
    }
    return next_command;
};
