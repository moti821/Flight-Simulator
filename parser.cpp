#include "parser.hpp"

Parser::Parser()
{
    commands["openDataServer"] = new OpenServerCommand;
    commands["connect"] = new ConnectCommand;
    commands["var"] = new VarCommand;
    commands["equal"] = new EqualCommand;
    commands["while"] = new WhileCommand;
    commands["print"] = new PrintCommand;
    commands["sleep"] = new SleepCommand;
}

Command *Parser::parse(std::vector<std::string> &line)
{
    Command *next_command = commands[line[0]];
    if(next_command == (Command*)0x0)
    {
        next_command = commands["equal"];
    }
    return next_command;
};
