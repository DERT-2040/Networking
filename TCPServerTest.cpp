#include <unistd.h>
#include <stdio.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <string.h>
#include <iostream>

#define PORT 2024

using namespace std;

int main()
{
  int serverFd, clientFd;
  struct sockaddr_in address;
  int addrlen = sizeof(address);
  char buffer[1024] = {0};
  int opt = 1;

  address.sin_family = AF_INET;
  address.sin_addr.s_addr = INADDR_ANY;
  address.sin_port = htons(PORT);

  serverFd = socket(AF_INET, SOCK_STREAM, 0);                                   //Socket() returns a file descriptor to the opened socket
  if(serverFd == -1)                                                            //AF_INET is IPv4, SOCK_STREAM is TCP, 0 is IP(Internet Protocol)
  {
    cout << "failed to create file descriptor" << endl;
  }

  int sso = setsockopt(serverFd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &opt, sizeof(opt));   //Prevents errors when when the port is being reused
  if(sso == -1)
  {
    cout << "setsockopt failed" << endl;
  }

  if(bind(serverFd, (struct sockaddr *)&address, sizeof(address)) == -1)
  {
    cout << "bind failed" << endl;
  }

  listen(serverFd, 1);

  if((clientFd = accept(serverFd, (struct sockaddr *)&address, (socklen_t*)&addrlen)) == -1)
  {
    cout << "accept error" << endl;
  }

  if(read(clientFd, buffer, 1024) == -1)
  {
    cout << "read faliure" << endl;
  }

  cout << buffer << endl;



}
