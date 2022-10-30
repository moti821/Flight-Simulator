#pragma once
#include <vector>
#include <thread>

class Server
{
public:
    static Server *get_instance();
    void open_connect();
    void open_simulator();
    static std::array<std::string, 36> name_to_number;


private:
    static Server *instance;
    Server();
    std::thread t1;
    std::thread t2;

    int port = 5400;
    int rhythm;
};