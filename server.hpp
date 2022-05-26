#pragma once
#include <netinet/in.h> // For sockaddr_in
#include <vector>
#include <string>
#include <thread>
#include <sys/socket.h> // For socket functions
#include <cstdlib>      // For exit() and EXIT_FAILURE
#include <iostream>     // For cout
#include <unistd.h>     // For read
#include <cstring>
#include "data_base.hpp"


class Server
{
public:
    static Server *getInstance(std::vector<std::string> lin);
    void opne_connect();
    void split_buffer(std::string);
    static std::array<std::string, 36> name_to_number;


private:
    static Server *instance;
    Server(std::vector<std::string>);
    // std::vector<std::string> paths;
    std::thread t1;

    int port = 5400;
    int rhythm;
};