#include <stdio.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <string.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <iostream>
#define PORT 30

using namespace std;

int main()
{
	int socket_fd;
	struct sockaddr_in address;
	struct sockaddr_in serv_addr;
	int addr_len = sizeof(address);

	socket_fd = socket(AF_INET, SOCK_STREAM, 0);
	if(socket_fd == -1)
	{
		cout << "failed to create socket" << endl;
	}
	
	inet_pton(AF_INET, "10.0.0.1", &address.sin_addr.s_addr);
	address.sin_family = AF_INET;
	address.sin_port = htons(PORT);

	if(connect(socket_fd, (struct sockaddr *)&address, addr_len) == -1)
	{
		cout << "failed to connect to server" << endl;
	}

	send(socket_fd, "help", sizeof("hello"), 0);

	return 0;
}
