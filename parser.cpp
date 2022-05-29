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
    if(!std::isalpha(line[0][0]))
    line[0] = delete_space(line[0]);

    Command *next_command = commands[line[0]];

    if(next_command == (Command*)0x0)
    next_command = commands["equal"];

    return next_command;
};

std::string Parser::delete_space(std::string original)
{
        std::string new_string;
        for (int i = 0; i < original.size(); i++)
        {
            if(!std::isalpha(original[i]))
            {
                original.erase(0,1);
            }
        }
        return original; 
}
