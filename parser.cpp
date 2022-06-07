#include "parser.hpp"

std::unordered_map <std::string, Command *> Parser::commands;
std::vector<int> Parser::vec_lines_to_while;


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

void Parser::create_hash()
{
    commands["openDataServer"] = new OpenServerCommand;
    commands["connect"] = new ConnectCommand;
    commands["var"] = new VarCommand;
    commands["equal"] = new EqualCommand;
    commands["while"] = new WhileCommand;
    commands["print"] = new PrintCommand;
    commands["sleep"] = new SleepCommand;
}

void Parser::parse()
{
    for (int i = 0; i < Lexer::get_instance()->get_size(); i++)
    {
        std::vector<std::string> line = Lexer::get_instance()->getLine(i);
        Command *next_command = commands[line[0]];
        if(!next_command) next_command = commands["equal"];

        if (line[0] == "while")
        {
            create_vec_line(i);
            next_command->do_command(i);
            i = vec_lines_to_while.back()+1;
        }      
        else next_command->do_command(i);

    }    

    return ;
};


void Parser::create_vec_line(int i)
{
    i++;
    vec_lines_to_while.clear();
    while(Lexer::get_instance()->getLine(i)[0] != "}")
    {
        vec_lines_to_while.push_back(i);
        i++;
    }
}

Command* Parser::get_command(std::string name_command)
{
    Command *next_command = commands[name_command];
    if(!next_command) next_command = commands["equal"];
    return next_command;
}