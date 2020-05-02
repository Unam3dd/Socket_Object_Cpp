#include "winbd_socket_object.h"

using namespace std;


// PUBLIC

Socket::Socket(short family, int type, int protocol)
{
	this->Socket::family = family;
	this->Socket::type = type;
	this->Socket::protocol = protocol;
	SOCKET socks = init_socket(); // socket init
	this->Socket::sobject = socks;
}

int Socket::Connect(string host, int port)
{
	this->Socket::host = host;
	this->Socket::port = port;
	sockaddr_in config = s_setting();
	if (connect(Socket::sobject, config) != -1)
	{
		return 1; // Connected !
	}
	else
	{
		return 0; // Fail Connect
	}
}

int Socket::SendData(char *data)
{
	if (send_data(Socket::sobject,data) != -1)
	{
		return 1; // Success !
	}
	else
	{
		return 0; // Fail !
	}
}

string Socket::RecvData(int bytes)
{
	char buffer[bytes];
	string output;
	memset(buffer, 0, sizeof(buffer));
	if (recv_data(Socket::sobject, buffer,(bytes-1)) != -1)
	{
		output = buffer;
		return output; // Success !
	}
	else
	{
		output = "[!] Error Recv Data !";
		return output; // Fail !
	}
}

// PRIVATE

SOCKET Socket::init_socket()
{
	SOCKET s;
	WSADATA wsa;

	WSAStartup(MAKEWORD(2, 2), &wsa);
	s = WSASocket(Socket::family,Socket::type,Socket::protocol, 0, 0, 0);
	return s;
}

sockaddr_in Socket::s_setting()
{
	struct sockaddr_in s;
	s.sin_family = Socket::family;
	s.sin_addr.s_addr = inet_addr(Socket::host.c_str());
	s.sin_port = htons(Socket::port);
	return s;
}