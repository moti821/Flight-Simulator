#include "server.hpp"

Server *Server::instance = 0;
void get_data(int connection, int sockfd);
DataBase* D_B = DataBase::get_instance();
std::array<std::string, 36> Server::name_to_number;
Server* serv = Server::getInstance({""});


Server *Server::getInstance(std::vector<std::string> lin)
{
  if (instance == 0)
  {
    instance = new Server(lin);
  };
  return instance;
};
Server::Server(std::vector<std::string> line_cmd){}


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
  std::cout << "connection pending" << std::endl;

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
  
  return;
}


void get_data(int connection, int sockfd)
{
  while (true)
  {
    // Read from the connection
    char buffer[1024] = {0};
    auto bytesRead = read(connection, buffer, 1024);
    // std::vector<double> values = 
    Server::getInstance({""})->split_buffer(buffer);
    // std::cout << "finish" << std::endl;
  }

  // Close the connections
  close(connection);
  close(sockfd);
};

void Server::split_buffer(std::string buffer)
{
  std::vector<double> values;
  values.clear();
  std::string oun_value;
  for(int i=0 ; i < buffer.size() ; i++)
  {
    if(buffer[i] == ',')
    {
      double value = 0;
      value = std::stod(oun_value);
      values.push_back(value);
      oun_value = "";
    }
    else
    {
      oun_value.push_back(buffer[i]);
    }
  }

  double value = 0;
  value = std::stod(oun_value);
  values.push_back(value);
  oun_value = "";

  // std::cout << "from server size of vulues is: " << values.size() << std::endl;
  for (int j = 0; j < serv->name_to_number.size() ; j++)
  {
    std::string name = serv->name_to_number[j];
    if(serv->name_to_number[j] != "")
    {
      D_B->symbol_table[serv->name_to_number[j]] = values[j];
      // std::cout << "name printing in server from name to number: " << name << " " << D_B->symbol_table[serv->name_to_number[j]] << std::endl;
    }
  }

  return;
}