#pragma once
#include <vector>
#include <string>

class Client
{
public:
    /* Static access method. */
    static Client *getInstance();
    void connect(std::vector<std::string>&);

private:
    /* Null, because instance will be initialized on demand. */
    static Client *instance;
    Client();
    void send(char *);
    int sock = 0, valread = 0;
    char buffer[1024] = {0};
    // char* command = "set controls/flight/rudder -1\r\n";
};