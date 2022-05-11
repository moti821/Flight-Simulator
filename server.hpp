#pragma once
#include <netinet/in.h> // For sockaddr_in
#include <vector>
#include <string>
#include <thread>

class Server
{
public:
    static Server *getInstance();
    std::thread connect(std::vector<std::string>);

private:
    int sockfd;
    int connection;
    sockaddr_in sockaddr;

    static Server *instance;
    Server();
    void get_data(int sockfd, int rhythm);
};