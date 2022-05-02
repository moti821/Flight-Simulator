

class Server
{
    public:
        static Server* getInstance();

    


    private:
        static Server* Server::instance;
        Server();

};