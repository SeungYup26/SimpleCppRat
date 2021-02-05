#include<iostream>
#include<string>
#include<WinSock2.h>
#include<Windows.h>

#pragma comment(lib, "ws2_32.lib")

const int port = 7677;
const int packet_size = 1024;

int main()
{
	WSADATA wsaData;
	WORD version = MAKEWORD(2, 2);
	WSAStartup(version, &wsaData);

	SOCKADDR_IN socket_address = {};
	socket_address.sin_family = AF_INET;
	socket_address.sin_addr.S_un.S_addr = INADDR_ANY;
	socket_address.sin_port = port;
	int socket_address_size = sizeof socket_address;

	SOCKET main_socket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

	bind(main_socket, reinterpret_cast<SOCKADDR*>(&socket_address), sizeof socket_address);
	listen(main_socket, SOMAXCONN);

	SOCKET client_socket = accept(main_socket, reinterpret_cast<SOCKADDR*>(&socket_address), &socket_address_size);
	
	char command[packet_size];
	char options[packet_size];

	while (true)
	{
		ZeroMemory(&command, packet_size);
		ZeroMemory(&options, packet_size);

		std::cout << " >>  ";
		std::cin >> command;

		send(client_socket, command, packet_size, 0);
		if (strcmp(command, "message") == 0)
		{
			std::cin >> options;
			send(client_socket, options, packet_size, 0);
			
			std::cin >> options;
			send(client_socket, options, packet_size, 0);
		}
	}

	std::cin.get();
	return 0;
}