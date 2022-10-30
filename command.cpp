#include <any>
#include <string>
#include <thread>
#include "command.hpp"
#include "lexer.hpp"
#include "server.hpp"
#include "client.hpp"
#include "parser.hpp"
#include "data_base.hpp"
#include "shunting_yard.cpp"

std::unordered_map<std::string, std::string> VarCommand::variable;
std::vector<std::string> paths = {"/instrumentation/airspeed-indicator/indicated-speed-kt", "/sim/time/warp", "/controls/switches/magnetos", "/instrumentation/heading-indicator/offset-deg", "/instrumentation/altimeter/indicated-altitude-ft", "/instrumentation/altimeter/pressure-alt-ft", "/instrumentation/attitude-indicator/indicated-pitch-deg", "/instrumentation/attitude-indicator/indicated-roll-deg", "/instrumentation/attitude-indicator/internal-pitch-deg", "/instrumentation/attitude-indicator/internal-roll-deg", "/instrumentation/encoder/indicated-altitude-ft", "/instrumentation/encoder/pressure-alt-ft", "/instrumentation/gps/indicated-altitude-ft", "/instrumentation/gps/indicated-ground-speed-kt", "/instrumentation/gps/indicated-vertical-speed", "/instrumentation/heading-indicator/indicated-heading-deg", "/instrumentation/magnetic-compass/indicated-heading-deg", "/instrumentation/slip-skid-ball/indicated-slip-skid", "/instrumentation/turn-indicator/indicated-turn-rate", "/instrumentation/vertical-speed-indicator/indicated-speed-fpm", "/controls/flight/aileron", "/controls/flight/elevator", "/controls/flight/rudder", "/controls/flight/flaps", "/controls/engines/engine/throttle", "/controls/engines/current-engine/throttle", "/controls/switches/master-avionics", "/controls/switches/starter", "/engines/active-engine/auto-start", "/controls/flight/speedbrake", "/sim/model/c172p/brake-parking", "/controls/engines/engine/primer", "/controls/engines/current-engine/mixture", "/controls/switches/master-bat", "/controls/switches/master-alt", "/engines/engine/rpm"};

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

        for (unsigned int j = 0; j < paths.size(); j++)
        {
            if (paths[j] == path_command)
                Server::get_instance()->name_to_number[j] = name_var;
        }

        variable[name_var] = path_command;
        DataBase::get_instance()->set_value(name_var, 0);
    }
    else
    {
        double value = DataBase::get_instance()->get_value(line_command[3]);
        DataBase::get_instance()->set_value(name_var, value);
    }
}

void EqualCommand::do_command(const std::vector<std::string> &line_command)
{
    
    if (line_command.size() > 1 && line_command[1] == "=")
    {
        VarCommand var;
        std::string string_line;
        for (unsigned int j = 2; j < line_command.size(); j++)
        {
            string_line += line_command[j];
        }

        std::string new_string = find_word_convert_to_value(string_line);

        Calculator c;
        std::string result = std::to_string(c.calculate(new_string));
        std::string message_is = "set " + var.variable[line_command[0]] + " " + result + "\r\n";
        char *message = &message_is[0];
        Client::getInstance()->send(message);
    }
    else
    {
        std::cout << "error: the command not found" << std::endl;
    }
}

std::string EqualCommand::find_word_convert_to_value(const std::string &str_line)
{
    std::string new_string;
    for (unsigned int k = 0; k < str_line.size(); k++)
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
            double value = DataBase::get_instance()->get_value(var_str);
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
    while (expression(DataBase::get_instance()->get_value(line_command[1]), line_command[2], val_condition))
    {
        for (int i : pars->vec_lines_to_while)
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
            for (unsigned int j = 2; j < line_command.size(); j++)
            {
                name += ' ';
                name += line_command[j];
            }
        }
        std::cout << name << std::endl;
    }
    else if (line_command.size() == 2)
    {
        std::cout << "The value of " << name << " is: " << DataBase::get_instance()->get_value(name) << std::endl;
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