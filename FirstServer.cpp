#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <iostream>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <string.h>
#include <stdio.h>
#include <errno.h>
#include <unistd.h>
#include <stdlib.h>
#include <sstream>

#define MAXBUF 1024

int main() {
	int Sock_1;
	int Sock_2;
	sockaddr_in self1;
	sockaddr_in self2;
	char buf[MAXBUF];
	if ((Sock_1 = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
		std::cout << "\nError in create socket\n" << std::endl;
		return -1;
	}
	if ((Sock_2 = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
		std::cout << "Error in create _self" << std::endl;
		return -1;
	}
	memset(&self2, 0, sizeof(self2));
	memset(&self1, 0, sizeof(self1));
	self2.sin_family= AF_INET;
	self2.sin_port = htons(8000);
	self2.sin_addr.s_addr = inet_addr("176.100.250.17");
	self1.sin_family = AF_INET;
	self1.sin_port = htons(8000);
	self1.sin_addr.s_addr = inet_addr("127.0.0.1");
	if (bind(Sock_1, (sockaddr*)&self1, sizeof(self1)) != 0) {
		std::cout << "\nError in connect socket\n" << std::endl;
		return -1;
	}
	if (bind(Sock_2, (sockaddr*)&self2, sizeof(self2)) != 0) {
		std::cout << "Error in connect _self" << std::endl;
		return -1;
	}
	if (listen(Sock_1, 20) != 0) {
		std::cout << "\nError in preparation socket to listen\n" << std::endl;
		return -1;
	}
	if (listen(Sock_2, 20) != 0) {
		std::cout << "Error in prep _self" << std::endl;
		return -1;
	}
	while(true) {
		int Client_Sock1;
		int Client_Sock2;
		sockaddr_in client_self1;
		sockaddr_in client_self2;
		unsigned int addrlen1 = sizeof(client_self1);
		unsigned int addrlen2 = sizeof(client_self2);
		Client_Sock1 = accept(Sock_1, (sockaddr*)&client_self1, &addrlen1);
		Client_Sock2 = accept(Sock_2, (sockaddr*)&client_self2, &addrlen2);
		std::cout << inet_ntoa(client_self1.sin_addr)
  		<< ":"
		<< ntohs(client_self1.sin_port)
		<< " Connected\n" << std::endl;
		std::cout << inet_ntoa(client_self2.sin_addr) 
		<< ":"
		<< ntohs(client_self2.sin_port)
		<< " Connected\n" << std::endl;
		std::string S;
		std::getline(std::cin, S);
		std::stringstream ss(S);
//		send(Client_Sock, buf, recv(Client_Sock, buf, MAXBUF, 0), 0);
//		send(Client_Sock, ss.str().c_str(), ss.str().length(), 0);
		send(Client_Sock2, ss.str().c_str(), ss.str().length(), 0);
		shutdown(Client_Sock1, 2);
		shutdown(Client_Sock2, 2);
//		shutdown(Sock_, 2);
		close(Client_Sock1);
		close(Client_Sock2);
		std::string s;
		std::cin >> s;
		if (s == "PAUSE")
			break;
	}
	std::cout << "\nServer paused\n" << std::endl;
	close(Sock_1);
	close(Sock_2);
	return 0;
}
		
