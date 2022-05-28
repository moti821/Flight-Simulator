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
    {
        std::string new_string;
        for (int i = 0; i < line[0].size(); i++)
        {
            if(std::isalpha(line[0][i]))
            {
                new_string += line[0][i];
            }
        }
        line[0] = new_string; 
        // std::cout << new_string <<std::endl;
    }
    Command *next_command = commands[line[0]];
    if(next_command == (Command*)0x0)
    {
        next_command = commands["equal"];
    }
    return next_command;
};
