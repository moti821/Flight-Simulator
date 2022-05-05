#include <sys/socket.h> // For socket functions
#include <cstdlib> // For exit() and EXIT_FAILURE
#include <iostream> // For cout
#include <unistd.h> // For read
#include "server.hpp"

Server* Server::instance = 0;

Server* Server::getInstance()
{
    if (instance == 0){
       instance = new Server();
    };
    return instance;       
};
Server::Server(){}


void Server::connect()
{
  // Create a socket (IPv4, TCP)
  sockfd = socket(AF_INET, SOCK_STREAM, 0);
  if (sockfd == -1) {
    std::cout << "Failed to create socket. errno: " << errno << std::endl;
    exit(EXIT_FAILURE);
  }

  // Listen to port 5400 on any address
  sockaddr.sin_family = AF_INET;
  sockaddr.sin_addr.s_addr = INADDR_ANY;
  sockaddr.sin_port = htons(5400); // htons is necessary to convert a number to
                                   // network byte order
  if (bind(sockfd, (struct sockaddr*)&sockaddr, sizeof(sockaddr)) < 0) {
    std::cout << "Failed to bind to port 9999. errno: " << errno << std::endl;
    exit(EXIT_FAILURE);
  }

  get_data(sockfd);

  return;
}


void Server::get_data(int sockfd)
{
  // Start listening. Hold at most 10 connections in the queue
  if (listen(sockfd, 10) < 0) {
    std::cout << "Failed to listen on socket. errno: " << errno << std::endl;
    exit(EXIT_FAILURE);
  }
  // Grab a connection from the queue
  auto addrlen = sizeof(sockaddr);
  connection = accept(sockfd, (struct sockaddr*)&sockaddr, (socklen_t*)&addrlen);
  if (connection < 0) {
    std::cout << "Failed to grab connection. errno: " << errno << std::endl;
    exit(EXIT_FAILURE);
  }
  while(true){

    // Read from the connection
    char buffer[100];
    auto bytesRead = read(connection, buffer, 100);
    std::cout << "The message was: " << buffer;

    // Send a message to the connection
    std::string response = "Good talking to you\n";
    send(connection, response.c_str(), response.size(), 0);
  }
 
  // Close the connections
  close(connection);
  close(sockfd);
};



// int main()
// {
//   Server::getInstance()->connect();
// }