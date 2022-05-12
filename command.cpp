#include <iostream>
// #include <thread>
#include "command.hpp"
#include "server.hpp"
#include "client.hpp"
#include <any>
#include <string>

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
    char* command = "set controls/flight/rudder 1\r\n";

    Client::getInstance()->connect(port, ip, command);
}

void VarCommand::do_command(std::vector<std::string>& line_command)
{
    if((line_command[3] == "bind") && (line_command.size() == 5))
    {
        variable[line_command[1]] = line_command[4];
    }else{
        variable[line_command[1]] = "//";
    }
}

void WhileCommand::do_command(std::vector<std::string>& line_command)
{

}