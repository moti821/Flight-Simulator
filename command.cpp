#include "command.hpp"
#include "server.hpp"
#include "client.hpp"


void Openservercommand::do_command()
{
    Server::getInstance()->connect();
}

void Connectcommand::do_command()
{
    Client::getInstance()->connect(5402,"127.0.0.1","set controls/flight/rudder 0\r\n");
}