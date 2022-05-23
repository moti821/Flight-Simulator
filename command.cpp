#include <iostream>
#include "command.hpp"
#include "client.hpp"
#include <any>
#include <string>

std::unordered_map<std::string, std::string> VarCommand::variable;
std::vector<std::string> paths;

void OpenServerCommand::do_command(std::vector<std::string>& line_command)
{
    if (line_command.size() != 3)
    {
        std::cout << "Enter port and rhythm" << std::endl;
    }
    Server::getInstance(line_command)->opne_connect();
}

void ConnectCommand::do_command(std::vector<std::string>& line_command)
{

    if (line_command.size() != 3)
    {
        std::cout << "Enter port ip and command" << std::endl;
    }

    std::string ip = line_command[1];
    int port = stoi(line_command[2]);
    std::this_thread::sleep_for (std::chrono::seconds(30));

    Client::getInstance()->connect(port, ip);
}

void VarCommand::do_command(std::vector<std::string>& line_command)
{
    paths = {"/instrumentation/airspeed-indicator/indicated-speed-kt","/sim/time/warp","/controls/switches/magnetos","/instrumentation/heading-indicator/offset-deg","/instrumentation/altimeter/indicated-altitude-ft","/instrumentation/altimeter/pressure-alt-ft","/instrumentation/attitude-indicator/indicated-pitch-deg","/instrumentation/attitude-indicator/indicated-roll-deg","/instrumentation/attitude-indicator/internal-pitch-deg","/instrumentation/attitude-indicator/internal-roll-deg","/instrumentation/encoder/indicated-altitude-ft","/instrumentation/encoder/pressure-alt-ft","/instrumentation/gps/indicated-altitude-ft","/instrumentation/gps/indicated-ground-speed-kt","/instrumentation/gps/indicated-vertical-speed","/instrumentation/heading-indicator/indicated-heading-deg","/instrumentation/magnetic-compass/indicated-heading-deg","/instrumentation/slip-skid-ball/indicated-slip-skid","/instrumentation/turn-indicator/indicated-turn-rate","/instrumentation/vertical-speed-indicator/indicated-speed-fpm","/controls/flight/aileron","/controls/flight/elevator","/controls/flight/rudder","/controls/flight/flaps","/controls/engines/engine/throttle","/controls/engines/current-engine/throttle","/controls/switches/master-avionics","/controls/switches/starter","/engines/active-engine/auto-start","/controls/flight/speedbrake" ,"/sim/model/c172p/brake-parking","/controls/engines/engine/primer","/controls/engines/current-engine/mixture","/controls/switches/master-bat","/controls/switches/master-alt","/engines/engine/rpm"};
    std::string name_var = line_command[1];
    std::string path_command = line_command[4];
    path_command.erase(0,1), path_command.pop_back();
    // std::string x;
    // std::cin >> x;
    if((line_command[3] == "bind") && (line_command.size() == 5))
    {

        for (int i = 0; i < paths.size(); i++)
        {
            if(paths[i] == path_command)
            {
                Server::getInstance({""})->name_to_number[i] = name_var;
            }
            // std::pair<std::string, int> pair_to_name(line_command[1],i);
        }
        
        variable[name_var] = path_command;
        DataBase::get_instance()->symbol_table[name_var] = 0;
        std::cout << "name print in command: " << name_var << std::endl;
        std::cout << "symbol table print in var command: " << DataBase::get_instance()->symbol_table[name_var] << std::endl;
    }
    else{
        DataBase::get_instance()->symbol_table[name_var] = DataBase::get_instance()->symbol_table[line_command[3]];
    }
}


void EqualCommand::do_command(std::vector<std::string>& line_command)
{
    if (line_command[1] == "=")
    {
        VarCommand* var = new VarCommand;
        std::unordered_map<std::string, std::string> variable = var->variable;
        std::string massage = "set " + var->variable[line_command[0]] + " " + line_command[2] + "\r\n";
        char* mass = &massage[0];
        Client::getInstance()->send(mass);
        std::string x;
        std::cin >> x;
    }
}

void WhileCommand::do_command(std::vector<std::string>& line_command)
{
    //
}

void PrintCommand::do_command(std::vector<std::string>& line_command)
{
    std::string name = line_command[1];
    if (line_command[2][0] == '"')
    {
        std::cout << name << std::endl;
    }
    else if(line_command.size() == 2)
    {
        std::cout << "The " << name << "is: " << DataBase::get_instance()->symbol_table[name] << std::endl;
    }
    else{
        std::cout << "EROOR" << std::endl;
    }
    
}

void SleepCommand::do_command(std::vector<std::string>& line_command)
{
    //
}