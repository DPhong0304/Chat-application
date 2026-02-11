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

#define NAMELEN 100
#define BUFSIZE 4096

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
    Address peeraddr;   
    std::string peername;

public:
    StreamSocket();
    StreamSocket(int port);
    StreamSocket(int port, const std::string& ipaddr);
    StreamSocket(int fd, Address peeraddr, const std::string& peername = "???????");// for accept
    ~StreamSocket();

    //copy semantics deleted
    StreamSocket(const StreamSocket&) = delete;
    StreamSocket& operator=(const StreamSocket& other) = delete;

    //move semantics added
    StreamSocket(StreamSocket&& other);
    StreamSocket& operator=(StreamSocket&& other); 
    int SSconnect(const std::string& ip, int port);
    void SSlisten(int backlog);
    int SSbind(const std::string& ipaddr);
    StreamSocket SSaccept();
    void SSsend(const std::string& mesg);
    std::string SSrecv();
    int getfd() const;
    std::string getpeername() const;
    std::string getpeerip_P() const;
    void setpeername(const std::string& name);
};
