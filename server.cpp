#include <netinet/in.h> // For sockaddr_in
#include <string>
#include <sys/socket.h> // For socket functions
#include <cstdlib>      // For exit() and EXIT_FAILURE
#include <iostream>     // For cout
#include <unistd.h>     // For read
#include <cstring>
#include "data_base.hpp"
#include "server.hpp"
#include "tools.hpp"

Server *Server::instance = 0;
void get_data(int connection, int sockfd);
std::array<std::string, 36> Server::name_to_number;

Server *Server::get_instance()
{
  if (instance == 0)
  {
    instance = new Server();
  };
  return instance;
}
Server::Server() {}

void Server::open_connect()
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
  std::cout << "connection pending" << std::endl;

  // Start listening. Hold at most 10 connections in the queue
  if (listen(sockfd, 10) < 0)
  {
    std::cout << "Failed to listen on socket. errno: " << errno << std::endl;
    exit(EXIT_FAILURE);
  }
  t1 = std::thread(&Server::open_simulator, this);
  // Grab a connection from the queue
  auto addrlen = sizeof(sockaddr);
  connection = accept(sockfd, (struct sockaddr *)&sockaddr, (socklen_t *)&addrlen);
  if (connection < 0)
  {
    std::cout << "Failed to grab connection. errno: " << errno << std::endl;
    exit(EXIT_FAILURE);
  }

  t2 = std::thread(get_data, connection, sockfd);
}

void Server::open_simulator()
{
  system("fgfs --telnet=socket,in,10,127.0.0.1,5402,tcp --generic=socket,out,10,127.0.0.1,5400,tcp,generic_small");
}

void get_data(int connection, int sockfd)
{
  while (true)
  {
    // Read from the connection
    char buffer[1024] = {0};
    read(connection, buffer, 1024);

    std::vector<std::string> values;
    split_string(buffer, ',', values);

    for (size_t j = 0; j < Server::get_instance()->name_to_number.size(); j++)
    {
      std::string name = Server::get_instance()->name_to_number[j];
      if (name != "")
      {
        DataBase::get_instance()->set_value(name, std::stod(values[j]));
      }
    }
  }

  // Close the connections
  close(connection);
  close(sockfd);
}