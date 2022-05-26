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

void OpenServerCommand::do_command(int i)
{
    std::vector<std::string> line_command = lex->getLine(i);
    if (line_command.size() != 3)
    {
        std::cout << "Enter port and rhythm" << std::endl;
    }
    Server::getInstance(line_command)->opne_connect();
}

void ConnectCommand::do_command(int i)
{
    std::vector<std::string> line_command = lex->getLine(i);
    if (line_command.size() != 3)
    {
        std::cout << "Enter port ip and command" << std::endl;
    }

    std::string ip = line_command[1];
    int port = stoi(line_command[2]);

    Client::getInstance()->connect(port, ip);
}

void VarCommand::do_command(int i)
{
    std::vector<std::string> line_command = lex->getLine(i);
    std::string name_var = line_command[1];

    if((line_command[3] == "bind") && (line_command.size() == 5))
    {
    std::string path_command = line_command[4];
    path_command.erase(0,1), path_command.pop_back();

        for (int i = 0; i < paths.size(); i++)
        {
            if(paths[i] == path_command)
            {
                Server::getInstance({""})->name_to_number[i] = name_var;
            }
        }
        
        variable[name_var] = path_command;
        DataBase::get_instance()->symbol_table[name_var] = 0;
        std::cout << "from var command vlue of " << name_var << " is: " << DataBase::get_instance()->symbol_table[name_var] << std::endl;
    }
    else{
        DataBase::get_instance()->symbol_table[name_var] = DataBase::get_instance()->symbol_table[line_command[3]];
        std::cout << "from var command value of "<< name_var <<" is: " << DataBase::get_instance()->symbol_table[name_var] << std::endl;
    }
}


void EqualCommand::do_command(int i)
{
    std::vector<std::string> line_command = lex->getLine(i);

    if(!std::isalpha(line_command[0][0]))
    {
        std::string new_string;
        for (int j = 0; j < line_command[0].size(); j++)
        {
            if(std::isalpha(line_command[0][i]))
            {
                new_string += line_command[0][i];
            }
        }
        line_command[0] = new_string; 
    }

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
                std::cout << "from equle command value of "<< var_str <<" in symbool table is: " << value << std::endl; 
                new_string += std::to_string(value);                
            }
            else{
            new_string += string_line[k];
            std::cout << "and new string is: " << new_string << std::endl;
            }
             
        }        
            // std::cout << "new string is: " << new_string << std::endl;
        Calculator c;
        std::string result = std::to_string(c.calculate(new_string));
        VarCommand* var = new VarCommand;
    std::cout << "From the equal command, the line is: " << line_command[0] << std::endl;
        std::string massage = "set " + var->variable[line_command[0]] + " " + result + "\r\n";
        char* mass = &massage[0];
        // std::string x;
        // std::cin >> x;
        Client::getInstance()->send(mass);        
    }
    else
    {
        std::cout << "Hi from the equal command it is not work" << std::endl;
    }
}

void WhileCommand::do_command(int i)
{
    std::cout << "Hi I am a whil command" << std::endl;
    std::vector<std::string> line_command = lex->getLine(i);


    if(line_command.size() != 5)
    {
        std::cout << "error" << std::endl;
        return;
    }
    create_vec_line(i);
    Parser pars;
    double condition = std::stod(line_command[3]);
    while(DataBase::get_instance()->symbol_table[line_command[1]] < condition)
    {
        for (int i : while_lines)
        {
            // std::cout << "hi I am into the while loop line: " << i<< std::endl;
            std::vector<std::string> line_command = lex->getLine(i);
            Command* command = pars.parse(line_command);
            command->do_command(i);
        }
        
    }
};

void WhileCommand::create_vec_line(int i)
{
    std::cout << "now I creat vec line" << std::endl;
    i++;
    while(lex->getLine(i)[0] != "}")
    {
        while_lines.push_back(i);
        i++;
    }
}

int WhileCommand::next_line()
{
    return while_lines.back()+1;
}

void PrintCommand::do_command(int i)
{
    std::cout << "This is the printer" << std::endl;
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
    
}

void SleepCommand::do_command(int i)
{
    std::vector<std::string> line_command = lex->getLine(i);
    std::this_thread::sleep_for(std::chrono::milliseconds(std::stoi(line_command[1])));
}
       