#pragma once
#include <netinet/in.h> // For sockaddr_in

class Server
{
    public:
        static Server* getInstance();
        void connect();


    private:
        int sockfd;
        int connection; 
        sockaddr_in sockaddr;

        static Server* instance;
        Server();
        void get_data(int);   


};