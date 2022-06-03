#include "parser.hpp"
std::unordered_map <std::string, Command *> Parser::commands;


Parser::Parser(){}

Parser::~Parser()
{
    delete commands["openDataServer"];
    delete commands["connect"];
    delete commands["var"];
    delete commands["equal"];
    delete commands["while"];
    delete commands["print"];
    delete commands["sleep"];

}

void Parser::creat_hash()
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

std::string Parser::find_word_convert_to_value(std::string str_line)
{
    std::string new_string;
    for (int k = 0; k < str_line.size(); k++)
    {
        if(isalpha(str_line[k]))
        {
            std::string var_str;
            while (isalpha(str_line[k]) || isdigit(str_line[k]))
            {
                var_str += str_line[k];
                k++;
            }
            k--;
            double value = DataBase::get_instance()->get_value(var_str);
            new_string += std::to_string(value);                
        }
        else{
        new_string += str_line[k];
        }             
    }   
    return new_string;   
}
