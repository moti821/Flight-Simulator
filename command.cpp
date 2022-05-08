#include <iostream>
#include "command.hpp"
#include "server.hpp"
#include "client.hpp"
#include <any>

void Openservercommand::do_command(std::vector<std::string> line_command)
{
    if (line_command.size() != 3)
    {
        std::cout << "Enter port and rhythm" << std::endl;
    }
    // Server::getInstance()->connect(line_command);
}

void Connectcommand::do_command(std::vector<std::string> line_command)
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