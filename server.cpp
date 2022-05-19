#include "server.hpp"

Server *Server::instance = 0;

void get_data(int connection, int sockfd);


Server *Server::getInstance(std::vector<std::string> lin)
{
  if (instance == 0)
  {
    instance = new Server(lin);
  };
  return instance;
};


Server::Server(std::vector<std::string> line_cmd) {}

void Server::opne_connect()
{
  int sockfd;
  int connection;
  sockfd = socket(AF_INET, SOCK_STREAM, 0); // Create a socket (IPv4, TCP)
  if (sockfd == -1)
  {
    std::cout << "Failed to create socket. errno: " << errno << std::endl;
    exit(EXIT_FAILURE);
  }

  // Listen to port 5400 on any address
  sockaddr_in sockaddr;
  sockaddr.sin_family = AF_INET;
  sockaddr.sin_addr.s_addr = INADDR_ANY;
  sockaddr.sin_port = htons(port); // htons is necessary to convert a number to
                                   // network byte order
  if (bind(sockfd, (struct sockaddr *)&sockaddr, sizeof(sockaddr)) < 0)
  {
    std::cout << "Failed to bind to port 9999. errno: " << errno << std::endl;
    exit(EXIT_FAILURE);
  }
  std::cout << "connection" << std::endl;

  // Start listening. Hold at most 10 connections in the queue
  if (listen(sockfd, 10) < 0)
  {
    std::cout << "Failed to listen on socket. errno: " << errno << std::endl;
    exit(EXIT_FAILURE);
  }
  // Grab a connection from the queue
  auto addrlen = sizeof(sockaddr);
  connection = accept(sockfd, (struct sockaddr *)&sockaddr, (socklen_t *)&addrlen);
  if (connection < 0)
  {
    std::cout << "Failed to grab connection. errno: " << errno << std::endl;
    exit(EXIT_FAILURE);
  }
  t1 = std::thread(get_data,connection, sockfd);
}


void get_data(int connection, int sockfd)
{
  while (true)
  {
    // Read from the connection
    char buffer[1000];
    auto bytesRead = read(connection, buffer, 1000);
    //std::cout << "The message was: " << buffer;

    // Send a message to the connection
    std::string response = "Good talking to you\n";
    send(connection, response.c_str(), response.size(), 0);
  }

  // Close the connections
  close(connection);
  close(sockfd);
};