#include "StreamSocket.h"

using namespace std;

StreamSocket::StreamSocket()
: domain(AF_INET), protocol(0), connected(false), type(SOCK_STREAM)
{
    fd = socket(domain, type, protocol);
}

void StreamSocket::SSbind(const string& ipaddr){
    memset(&addr, 0, sizeof(Address));
    addr.sin_family = domain;
    inet_pton(domain, ipaddr.c_str(), &(addr.sin_addr));
    addr.sin_port = htons(port);
    bind(fd, (sockaddr*) &addr, sizeof(Address));
}
 
StreamSocket::StreamSocket(int port, const string& ipaddr)
: StreamSocket{}
{
    this->port = port;
    StreamSocket::SSbind(ipaddr);
}

void StreamSocket::SSconnect(const std::string& ipaddr, int port){
    memset(&peeraddr, 0, sizeof(Address));
    peeraddr.sin_family = domain;
    inet_pton(domain, ipaddr.c_str(), &(peeraddr.sin_addr));
    peeraddr.sin_port = htons(port);
    connect(fd, (sockaddr*) &peeraddr, sizeof(Address));
}

// StreamSocket& StreamSocket::operator=(StreamSocket& other){
//     fd = other.fd;
//     other.fd = -1;
//     domain = other.domain;
//     connected = other.connected;
//     return *this;
// }

StreamSocket::StreamSocket(int fd, Address peeraddr, string& peername)
: fd{fd}, peeraddr{peeraddr}, peername{peername}
{
}

StreamSocket StreamSocket::SSaccept() {
    socklen_t len = sizeof(peeraddr);
    int connfd = accept(fd, (sockaddr*)&peeraddr, &len);
    char buff[NAMELEN];
    recv(connfd, buff, sizeof(buff), 0);
    peername = string(buff);
    return StreamSocket(connfd, peeraddr, peername);
}

void StreamSocket::SSlisten(int backlog){
    listen(fd, backlog);
}

StreamSocket::~StreamSocket(){
    if (fd != -1)
        close(fd);
}

int StreamSocket::getfd() const{
    return fd;
}

string StreamSocket::getpeername() const{
    return peername;
}

string StreamSocket::getpeerip_P() const{
    char buf[INET_ADDRSTRLEN];
    inet_ntop(domain, &(peeraddr.sin_addr), buf, INET_ADDRSTRLEN);
    return buf;
}

void StreamSocket::SSsend(string& mesg){
    send(fd, mesg.c_str(), mesg.size(), 0);
}

string StreamSocket::SSrecv(){
    char buf[BUFSIZE];
    ssize_t numRead = recv(fd, buf, BUFSIZE, 0);
    return string(buf, numRead);
}