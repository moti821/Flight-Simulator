#include <iostream>
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
    //Server::getInstance(line_command)->opne_connect();
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
    // std::cin >> x;
    if((line_command[3] == "bind") && (line_command.size() == 5))
    {
        variable[line_command[1]] = line_command[4];
        std::cout << "var is: " << variable[line_command[1]] << std::endl;
    }
    else{
        variable[line_command[1]] = "//";
    }
}

void EqualCommand::do_command(std::vector<std::string>& line_command)
{
    if (line_command[1] == "=")
    {
        std::cout << "is: " << variable[line_command[0]] << std::endl;
        std::string massage = "set " + variable[line_command[0]] + "\r\n " + line_command[2];
        std::cout << massage << std::endl;
        char* mass = &massage[0];
        Client::getInstance()->send(mass);
    }
}

void WhileCommand::do_command(std::vector<std::string>& line_command)
{

}