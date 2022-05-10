#include "parser.hpp"

Parser::Parser()
{
    commands["openDataServer"] = new Openservercommand;
    commands["connect"] = new Connectcommand;
}

Command* Parser::parse(std::vector<std::string>& line)
{
    Command *next_command = commands[line[0]];
    return next_command;        
};
