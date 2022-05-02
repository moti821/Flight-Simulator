

class Server
{
    public:
        static Server* getInstance();
        void connect();


    private:
        int sockfd;
        int connection; //= accept(sockfd, (struct sockaddr*)&sockaddr, (socklen_t*)&addrlen);
        sockaddr_in sockaddr;

        static Server* instance;
        Server();
        void get_data(int);   


};