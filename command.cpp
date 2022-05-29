#include <iostream>
#include "command.hpp"
#include "client.hpp"
#include "parser.hpp"
#include "shunting_yard.cpp"
#include <any>
#include <string>

std::unordered_map<std::string, std::string> VarCommand::variable;
std::vector<std::string> paths = {"/instrumentation/airspeed-indicator/indicated-speed-kt","/sim/time/warp","/controls/switches/magnetos","/instrumentation/heading-indicator/offset-deg","/instrumentation/altimeter/indicated-altitude-ft","/instrumentation/altimeter/pressure-alt-ft","/instrumentation/attitude-indicator/indicated-pitch-deg","/instrumentation/attitude-indicator/indicated-roll-deg","/instrumentation/attitude-indicator/internal-pitch-deg","/instrumentation/attitude-indicator/internal-roll-deg","/instrumentation/encoder/indicated-altitude-ft","/instrumentation/encoder/pressure-alt-ft","/instrumentation/gps/indicated-altitude-ft","/instrumentation/gps/indicated-ground-speed-kt","/instrumentation/gps/indicated-vertical-speed","/instrumentation/heading-indicator/indicated-heading-deg","/instrumentation/magnetic-compass/indicated-heading-deg","/instrumentation/slip-skid-ball/indicated-slip-skid","/instrumentation/turn-indicator/indicated-turn-rate","/instrumentation/vertical-speed-indicator/indicated-speed-fpm","/controls/flight/aileron","/controls/flight/elevator","/controls/flight/rudder","/controls/flight/flaps","/controls/engines/engine/throttle","/controls/engines/current-engine/throttle","/controls/switches/master-avionics","/controls/switches/starter","/engines/active-engine/auto-start","/controls/flight/speedbrake" ,"/sim/model/c172p/brake-parking","/controls/engines/engine/primer","/controls/engines/current-engine/mixture","/controls/switches/master-bat","/controls/switches/master-alt","/engines/engine/rpm"};
Lexer* lex = Lexer::get_instance();
Parser* pars = new Parser;

int OpenServerCommand::do_command(int i)
{
    std::vector<std::string> line_command = lex->getLine(i);
    if (line_command.size() != 3)
    {
        std::cout << "Enter port and rhythm" << std::endl;
        return 0;
    }
    Server::getInstance(line_command)->opne_connect();
    return i;
}

int ConnectCommand::do_command(int i)
{
    std::vector<std::string> line_command = lex->getLine(i);
    if (line_command.size() != 3)
    {
        std::cout << "Enter port ip and command" << std::endl;
        return 0;
    }

    std::string ip = line_command[1];
    int port = stoi(line_command[2]);

    Client::getInstance()->connect(port, ip);
    return i;
}

int VarCommand::do_command(int i)
{
    std::vector<std::string> line_command = lex->getLine(i);
    std::string name_var = line_command[1];

    if((line_command[3] == "bind") && (line_command.size() == 5))
    {
        std::string path_command = line_command[4];
        path_command.erase(0,1), path_command.pop_back();

        for (int j = 0; j < paths.size(); j++)
        {
            if(paths[j] == path_command)
            Server::getInstance({""})->name_to_number[j] = name_var;
        }
        
        variable[name_var] = path_command;
        DataBase::get_instance()->symbol_table[name_var] = 0;
    }
    else{
        DataBase::get_instance()->symbol_table[name_var] = DataBase::get_instance()->symbol_table[line_command[3]];
    }
    return i;
}

int EqualCommand::do_command(int i)
{
    std::vector<std::string> line_command = lex->getLine(i);

    if(!std::isalpha(line_command[0][0]))
    line_command[0] = pars->delete_space(line_command[0]); 

    if(line_command[1] == "=")
    {
        std::string string_line;
        for (int j = 2; j < line_command.size(); j++)
        {
            string_line += line_command[j];
        }

        std::string new_string;
        for (int k = 0; k < string_line.size(); k++)
        {
            if(isalpha(string_line[k]))
            {
                std::string var_str;
                while (isalpha(string_line[k]) || isdigit(string_line[k]))
                {
                    var_str += string_line[k];
                    k++;
                }
                k--;
                double value = DataBase::get_instance()->symbol_table[var_str];
                new_string += std::to_string(value);                
            }
            else{
            new_string += string_line[k];
            }             
        }       

        Calculator c;
        std::string result = std::to_string(c.calculate(new_string));
        VarCommand* var = new VarCommand;
        std::string massage = "set " + var->variable[line_command[0]] + " " + result + "\r\n";
        char* mass = &massage[0];
        Client::getInstance()->send(mass);        
    }
    else
    {
        std::cout << "Hi from the equal command it is not work" << std::endl;
    }
    return i;
}

int WhileCommand::do_command(int i)
{
    std::vector<std::string> line_command = lex->getLine(i);

    if(line_command.size() != 5)
    {
        std::cout << "error" << std::endl;
        return i;
    }

    create_vec_line(i);

    Parser pars;
    double condition = std::stod(line_command[3]);
    while(DataBase::get_instance()->symbol_table[line_command[1]] < condition)
    {
        for (int i : while_lines)
        {
            std::vector<std::string> line_command = lex->getLine(i);
            Command* command = pars.parse(line_command);
            command->do_command(i);
        }
        
    }
    return while_lines.back()+1;
};

void WhileCommand::create_vec_line(int i)
{
    i++;
    while_lines.clear();
    while(lex->getLine(i)[0] != "}")
    {
        while_lines.push_back(i);
        i++;
    }
}

int PrintCommand::do_command(int i)
{
    std::vector<std::string> line_command = lex->getLine(i);
    std::string name = line_command[1];
    if (name[0] == '"')
    {
        if(line_command.size() > 2)
        {
            for(int j = 2; j<line_command.size(); j++)
            {
                name += line_command[j]; 
            }
        }
        std::cout << name << std::endl;
    }
    else if(line_command.size() == 2)
    {
        std::cout << "The value of " << name << " is: " << DataBase::get_instance()->symbol_table[name] << std::endl;
    }
    else{
        std::cout << "EROOR" << std::endl;
    }
    return i;    
}

int SleepCommand::do_command(int i)
{
    std::vector<std::string> line_command = lex->getLine(i);
    std::cout << "sleeping " << line_command[1] << " milliseconds" << std::endl;
    std::this_thread::sleep_for(std::chrono::milliseconds(std::stoi(line_command[1])));
    return i;
}
       