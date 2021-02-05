#define _WINSOCK_DEPRECATED_NO_WARNINGS

#include<iostream>
#include<string>
#include<WinSock2.h>
#include<Windows.h>

#pragma comment(lib, "ws2_32.lib")

char address[] = "127.0.0.1";
const int port = 7677;

const int packet_size = 1024;

int main()
{
	WSADATA wsaData;
	WORD version = MAKEWORD(2, 2);
	WSAStartup(version, &wsaData);

	SOCKADDR_IN socket_address = {};
	socket_address.sin_family = AF_INET;
	socket_address.sin_addr.S_un.S_addr = inet_addr(address);
	socket_address.sin_port = port;
	
	SOCKET main_socket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

	connect(main_socket, reinterpret_cast<SOCKADDR*>(&socket_address), sizeof socket_address);

	char command[packet_size];
	char title[packet_size];
	char text[packet_size];

	while (true)
	{
		ZeroMemory(&command, packet_size);
		ZeroMemory(&title, packet_size);
		ZeroMemory(&text, packet_size);

		recv(main_socket, command, packet_size, 0);

		if(strcmp(command,"message") == 0)
		{
			recv(main_socket, title, packet_size, 0);
			recv(main_socket, text, packet_size, 0);

			MessageBoxA(NULL, text, title, MB_OK);
		}
	}
}