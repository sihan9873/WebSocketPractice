#pragma once
#include <string>
#include <cstring>

class XTcp
{
public:
	int CreateSocket();
	bool Bind(unsigned short port);
	//不能在析构中关闭socket,否则赋值等过程中会经常重复关闭
	XTcp Accept();
	void Close();
	int Recv(char* buf, int bufsize);
	int Send(const char* buf, int sendsize);
	XTcp();
	virtual ~XTcp();
	int sock = 0;
	unsigned short port = 0;
	std::string ip;
};

