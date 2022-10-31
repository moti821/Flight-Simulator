class Client
{
public:
    /* Static access method. */
    static Client *getInstance();
    void connect(int port, std::string ip);
    void send(std::string path, double value);

private:
    /* Null, because instance will be initialized on demand. */
    static Client *instance;
    Client();
    int sock = 0, valread = 0;
    char buffer[1024] = {0};
};