#include <vector>
#include "parser.hpp"
#include "lexer.hpp"
#include "command.hpp"

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

void Parser::parse(const std::string &path_file)
{
    Lexer *lex = new Lexer();
    lex->open_instructions_file(path_file);

    for (int i = 0; i < lex->get_size(); i++)
    {
        std::vector<std::string> line = lex->get_line(i);
        Command *next_command = commands[line[0]];
        if (!next_command)
            next_command = commands["equal"];

        if (line[0] == "while")
        {
            create_vec_line(i, lex);
            next_command->do_command(line);
            i = vec_lines_to_while.back() + 1;
            continue;
        }

        try
        {
            next_command->do_command(line);
        }
        catch (const std::exception &e)
        {
            std::cerr << e.what() << '\n';
            continue;
        }
    }
    delete lex;
}

void Parser::create_vec_line(int num_line, Lexer *lex)
{
    num_line++;
    vec_lines_to_while.clear();
    while (lex->get_line(num_line)[0] != "}")
    {
        vec_lines_to_while.push_back(num_line);
        num_line++;
    }
}

Command *Parser::get_command(const std::string &name_command)
{
    Command *next_command = commands[name_command];
    if (!next_command)
        next_command = commands["equal"];
    return next_command;
}