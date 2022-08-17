#pragma once
#include <vector>
#include <thread>

class Server
{
public:
    static Server *get_instance(std::vector<std::string> lin);
    void open_connect();
    static std::array<std::string, 36> name_to_number;
    void open_simulator();


private:
    static Server *instance;
    Server(std::vector<std::string>);
    std::thread t1;
    std::thread t2;

    int port = 5400;
    int rhythm;
};