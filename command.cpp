#include <iostream>
#include "command.hpp"
#include "server.hpp"
#include "client.hpp"
#include <any>
#include <string>

std::unordered_map<std::string, std::string> VarCommand::variable;


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

    Client::getInstance()->connect(port, ip);
}

void VarCommand::do_command(std::vector<std::string>& line_command)
{
    // std::cout << line_command[0] << std::endl;
    std::string x;
    std::cin >> x;
    if((line_command[3] == "bind") && (line_command.size() == 5))
    {
        std::string path_command = line_command[4];
        path_command.erase(0,1), path_command.pop_back();
        variable[line_command[1]] = path_command;
        std::cout << "var is: " << variable[line_command[1]] << std::endl;
    }
    else{
        variable[line_command[1]] = "//";
    }
}

// std::unordered_map<std::string, std::string>& VarCommand::get_H_map()
// {
//     if(variable.size() < 1)
//     {
//         std::cout << "Error: The map not defind" << std::endl;
//     };
//     return variable*;
// }

void EqualCommand::do_command(std::vector<std::string>& line_command)
{
    if (line_command[1] == "=")
    {
        VarCommand* var = new VarCommand;
        // std::unordered_map<std::string, std::string> variable = var->variable;
        // std::cout << "is: " << var->variable[line_command[0]] << std::endl;
        std::string massage = "set " + var->variable[line_command[0]] + " " + line_command[2] + "\r\n";
        std::cout << "massage is: " << massage << std::endl;
        char* mass = &massage[0];
        Client::getInstance()->send(mass);
    }
}

void WhileCommand::do_command(std::vector<std::string>& line_command)
{

}