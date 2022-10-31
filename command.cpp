#include <string>
#include "command.hpp"
#include "lexer.hpp"
#include "DBserver.hpp"
#include "client.hpp"
#include "parser.hpp"
#include "symbol_table.hpp"
#include "shunting_yard.cpp"


void OpenServerCommand::do_command(const std::vector<std::string> &line_command)
{
    if (line_command.size() != 3)
    {
        std::cout << "Enter port and rhythm" << std::endl;
        return;
    }
    Server::get_instance()->open_connect();
}

void ConnectCommand::do_command(const std::vector<std::string> &line_command)
{
    if (line_command.size() != 3)
    {
        std::cout << "Enter port ip and command" << std::endl;
        return;
    }

    std::string ip = line_command[1];
    int port = stoi(line_command[2]);

    Client::getInstance()->connect(port, ip);
}

SymbolTable* symbol_instance = SymbolTable::get_instance();

void VarCommand::do_command(const std::vector<std::string> &line_command)
{
    if (line_command.size() < 3)
    {
        std::cout << "Var need more arguments" << std::endl;
        return;
    }
    std::string name_var = line_command[1];

    if ((line_command[3] == "bind") && (line_command.size() == 5))
    {
        std::string path_command = line_command[4];
        path_command.erase(0, 1), path_command.pop_back();
        symbol_instance->set_var(name_var, path_command);
    }
    else
    {
        double value = symbol_instance->get_value(line_command[3]);
        symbol_instance->set_value(name_var, value);
    }
}

void AssignmentCommand::do_command(const std::vector<std::string> &line_command)
{
    
    if (line_command.size() > 1 && line_command[1] == "=")
    {
        std::string string_line;
        for (size_t j = 2; j < line_command.size(); j++)
        {
            string_line += line_command[j];
        }

        std::string new_string = find_word_convert_to_value(string_line);

        Calculator c;
        double value = c.calculate(new_string);
        symbol_instance->set_value(line_command[0], value);               
    }
    else
    {
        std::cout << "error: the command not found" << std::endl;
    }
}

std::string AssignmentCommand::find_word_convert_to_value(const std::string &str_line)
{
    std::string new_string;
    for (size_t k = 0; k < str_line.size(); k++)
    {
        if (isalpha(str_line[k]))
        {
            std::string var_str;
            while (isalpha(str_line[k]) || isdigit(str_line[k]))
            {
                var_str += str_line[k];
                k++;
            }
            k--;
            double value = symbol_instance->get_value(var_str);
            new_string += std::to_string(value);
        }
        else
        {
            new_string += str_line[k];
        }
    }
    return new_string;
}

void WhileCommand::do_command(const std::vector<std::string> &line_command)
{
    if (line_command.size() != 5)
    {
        std::cout << "error: the condition of while loop not clear" << std::endl;
        return;
    }
    Parser *pars = new Parser();
    Lexer *lex = new Lexer();
    double val_condition = std::stod(line_command[3]);
    while (expression(symbol_instance->get_value(line_command[1]), line_command[2], val_condition))
    {
        for (size_t i : pars->vec_lines_to_while)
        {
            std::vector<std::string> line_command = lex->get_line(i);
            try
            {
                Command *command = pars->get_command(line_command[0]);
                command->do_command(line_command);
            }
            catch (const std::exception &e)
            {
                std::cerr << e.what() << '\n';
                continue;
            }
        }
    }
    delete pars;
    delete lex;
}

bool WhileCommand::expression(double x, const std::string &operat, double y)
{
    if ((operat == "<") && (x < y))
        return true;
    else if ((operat == ">") && (x > y))
        return true;
    else if ((operat == ">=") && (x >= y))
        return true;
    else if ((operat == "<=") && (x <= y))
        return true;
    else if ((operat == "==") && (x == y))
        return true;
    else if ((operat == "!=") && (x != y))
        return true;

    return false;
}

void PrintCommand::do_command(const std::vector<std::string> &line_command)
{
    std::string name = line_command[1];
    if (name[0] == '"')
    {
        if (line_command.size() > 2)
        {
            for (size_t j = 2; j < line_command.size(); j++)
            {
                name += ' ';
                name += line_command[j];
            }
        }
        std::cout << name << std::endl;
    }
    else if (line_command.size() == 2)
    {
        std::cout << "The value of " << name << " is: " << symbol_instance->get_value(name) << std::endl;
    }
    else
    {
        std::cout << "EROOR: the ptinting not found" << std::endl;
    }
}

void SleepCommand::do_command(const std::vector<std::string> &line_command)
{
    std::cout << "sleeping " << line_command[1] << " milliseconds" << std::endl;
    std::this_thread::sleep_for(std::chrono::milliseconds(std::stoi(line_command[1])));
}