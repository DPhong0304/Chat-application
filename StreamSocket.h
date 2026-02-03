#pragma once
#include <sys/socket.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <netinet/in.h>
#include <errno.h>
#include <netdb.h>
#include <sys/select.h>
#include <string>
#include <string.h>
// #include <sys/types.h>

using Address = sockaddr_in;

class StreamSocket{
private:
    int fd;
    int domain;
    int protocol;
    bool connected;
    int type;
    int port;
    Address addr;

public:
    StreamSocket(int port, std::string& ipaddr);
    StreamSocket(int fd);                
    ~StreamSocket();
    void SSconnect();
    void SSbindandlisten(int backlog);
    StreamSocket SSaccept();
    int SSsend(string& mesg);
    std::string SSrecv();
};
