#include "server.hpp"
// #include "data_base.hpp"

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
    Server::getInstance({""})->split_buffer(buffer);

    // Send a message to the connection
    std::string response = "Good talking to you\n";
    send(connection, response.c_str(), response.size(), 0);
  }

  // Close the connections
  close(connection);
  close(sockfd);
};

void Server::split_buffer(std::string buffer)
{
  paths = {"/instrumentation/airspeed-indicator/indicated-speed-kt","/sim/time/warp","/controls/switches/magnetos","/instrumentation/heading-indicator/offset-deg","/instrumentation/altimeter/indicated-altitude-ft","/instrumentation/altimeter/pressure-alt-ft","/instrumentation/attitude-indicator/indicated-pitch-deg","/instrumentation/attitude-indicator/indicated-roll-deg","/instrumentation/attitude-indicator/internal-pitch-deg","/instrumentation/attitude-indicator/internal-roll-deg","/instrumentation/encoder/indicated-altitude-ft","/instrumentation/encoder/pressure-alt-ft","/instrumentation/gps/indicated-altitude-ft","/instrumentation/gps/indicated-ground-speed-kt","/instrumentation/gps/indicated-vertical-speed","/instrumentation/heading-indicator/indicated-heading-deg","/instrumentation/magnetic-compass/indicated-heading-deg","/instrumentation/slip-skid-ball/indicated-slip-skid","/instrumentation/turn-indicator/indicated-turn-rate","/instrumentation/vertical-speed-indicator/indicated-speed-fpm","/controls/flight/aileron","/controls/flight/elevator","/controls/flight/rudder","/controls/flight/flaps","/controls/engines/engine/throttle","/controls/engines/current-engine/throttle","/controls/switches/master-avionics","/controls/switches/starter","/engines/active-engine/auto-start","/controls/flight/speedbrake" ,"/sim/model/c172p/brake-parking","/controls/engines/engine/primer","/controls/engines/current-engine/mixture","/controls/switches/master-bat","/controls/switches/master-alt","/engines/engine/rpm"};
  std::vector<double> values;
  std::string oun_value;
  for(int i=0 ; i < buffer.size() ; i++)
  {
    if(buffer[i] != ',')
    {
      oun_value.push_back(buffer[i]);
    }
    else
    {
      double value = std::stod(oun_value);
      values.push_back(value);
      oun_value = "";
    }
  }

  for (int i = 0; i < values.size() ; i++)
  {
    DataBase::get_instance()->create_H_map();
    DataBase::get_instance()->symbol_table[paths[i]] = values[i];
    std::cout << DataBase::get_instance()->symbol_table[paths[i]] << " ";
  }
  std::cout << "finish" << std::endl;
  // DataBase* insta = DataBase::get_instance();
  // std::unordered_map<std::string, double> d = DataBase::get_instance()->symbol_table;

  return;
}