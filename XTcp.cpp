#include "XTcp.h"

#ifdef _WIN32
#define _WINSOCK_DEPRECATED_NO_WARNINGS
#include <winsock2.h>
#include <windows.h>
#include <ws2tcpip.h>
#pragma comment(lib, "ws2_32.lib")
typedef SOCKET socket_t;
#define socklen_t int
#else
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <arpa/inet.h>
#define closesocket close
typedef int socket_t;
#endif
#include <thread>
#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <cstring>
#include <string>

using namespace std;

XTcp::XTcp() {
#ifdef _WIN32
    static bool first = true;
    if (first) {
        first = false;
        WSADATA ws;
        WSAStartup(MAKEWORD(2, 2), &ws);
    }

#endif
}

int XTcp::CreateSocket() {
    //创建socket
    int sock = socket(AF_INET, SOCK_STREAM, 0);
    if (sock == -1) {
        printf("create socket failed!\n");       
    }
    printf("[%d] \n", sock);
    return sock;
}

bool XTcp::Bind(unsigned short port) {
    if (port <= 0) {
        CreateSocket();
    }
    //配置服务端地址
    //定义一个 IPv4 地址结构体变量
    sockaddr_in saddr;
    //设置地址格式
    saddr.sin_family = AF_INET;
    //设置端口号，并转换为网络字节序
    saddr.sin_port = htons(port);
    //设置IP地址为「本机任意地址」，并转换为网络字节序
    saddr.sin_addr.s_addr = htonl(0);

    //绑定Socket和地址
    if (bind(sock, (sockaddr*)&saddr, sizeof(saddr)) != 0) {
        printf("bind port %d failed!\n", port);
        return false;
    }
    printf("bind port %d success!\n", port);

    //监听,接收用户的连接
    //参数:套接字描述符;套接字请求队列的长度,是一个缓冲大小

    listen(sock, 10);

    return true;
}

XTcp XTcp::Accept() {
    XTcp tcp;

    sockaddr_in caddr;
#ifdef _WIN32
    int len = sizeof(caddr);
    #define ACCEPT_FAILED_VAL INVALID_SOCKET
#else
    socklen_t len = sizeof(caddr);
    #define ACCEPT_FAILED_VAL -1
#endif

    //int accept(int sockfd, struct sockaddr *addr, socklen_t *addrlen);
    int client = accept(sock, (sockaddr*)&caddr, &len);
    if (client == ACCEPT_FAILED_VAL) {
        return tcp;
    }
    printf("accept client %d\n", client);
    tcp.ip = inet_ntoa(caddr.sin_addr);
    tcp.port = ntohs(caddr.sin_port);
    printf("client ip is %s,port is %d\n", tcp.ip.c_str(), tcp.port);

    // 删掉临时宏，避免污染
    #undef ACCEPT_FAILED_VAL

    return tcp;
}

void XTcp::Close() {
    if (sock <= 0) {
        return;
    }
    closesocket(sock);
}

int XTcp::Recv(char* buf, int bufsize) {

    return recv(sock, buf, bufsize, 0);
}

int XTcp::Send(const char* buf, int sendsize) {
    int sendedSize = 0;
    while (sendedSize != sendsize) {
        int len = send(sock, buf + sendedSize, sendsize - sendedSize,0);
        if (len <= 0) {
            break;
        }
        sendedSize += len;
    }
    return sendedSize;
}

XTcp::~XTcp()
{

}
