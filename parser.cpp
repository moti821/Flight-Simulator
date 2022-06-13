#include <vector>
#include "parser.hpp"
#include "lexer.hpp"

std::vector<int> Parser::vec_lines_to_while;


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
        else{
            try
            {
                next_command->do_command(i);
            }
            catch(const std::exception& e)
            {
                std::cerr << e.what() << '\n';
                continue;
            }
            

        } 
    }    
    return ;
};

void Parser::create_vec_line(int num_line)
{
    num_line++;
    vec_lines_to_while.clear();
    while(Lexer::get_instance()->getLine(num_line)[0] != "}")
    {
        vec_lines_to_while.push_back(num_line);
        num_line++;
    }
}

Command* Parser::get_command(std::string name_command)
{
    Command *next_command = commands[name_command];
    if(!next_command) next_command = commands["equal"];
    return next_command;
}