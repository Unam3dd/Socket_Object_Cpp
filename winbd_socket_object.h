#pragma once
#include <iostream>
#include "socket_winbd.h"

using namespace std;

class Socket
{

public:
	Socket(short family,int type,int protocol);
	int Connect(string host,int port);
	int SendData(char *data);
	string RecvData(int bytes);

private:
	string host;
	int port;
	short family;
	int type;
	int protocol;
	SOCKET sobject;

	SOCKET init_socket();
	sockaddr_in s_setting();
};