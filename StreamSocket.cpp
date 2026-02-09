#include "StreamSocket.h"
#include <iostream>

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
    cout << "Bound to " << ipaddr << " on port " << port << endl;
}
 
StreamSocket::StreamSocket(int port, const string& ipaddr)
: StreamSocket{}
{
    this->port = port;
    StreamSocket::SSbind(ipaddr);
}

int StreamSocket::SSconnect(const std::string& ipaddr, int port){
    memset(&peeraddr, 0, sizeof(Address));
    peeraddr.sin_family = domain;
    inet_pton(domain, ipaddr.c_str(), &(peeraddr.sin_addr));
    peeraddr.sin_port = htons(port);
    int result = connect(fd, (sockaddr*) &peeraddr, sizeof(Address));
    if (result == -1) {
        perror("connect");
        return -1;
    }
    else{
        cout << "Connected to " << ipaddr << " on port " << port << endl;
    }
    return result;
}

StreamSocket::StreamSocket(int fd, Address peeraddr, const string& peername)
: fd{fd}, peeraddr{peeraddr}, peername{peername}, domain{AF_INET}, protocol{0}, connected{true}, type{SOCK_STREAM}
{
}

void StreamSocket::setpeername(const string& name){
    peername = name;
}

StreamSocket StreamSocket::SSaccept() {
    socklen_t len = sizeof(peeraddr);
    int connfd = accept(fd, (sockaddr*)&peeraddr, &len);
    peername = "??????"; 
    return StreamSocket(connfd, peeraddr, peername);
}

void StreamSocket::SSlisten(int backlog){
    listen(fd, backlog);
    cout << "Listening on port " << port << endl;
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
    return string(buf);
}

void StreamSocket::SSsend(string& mesg){
    send(fd, mesg.c_str(), mesg.size(), 0);
}

string StreamSocket::SSrecv(){
    char buf[BUFSIZE];
    ssize_t numRead = recv(fd, buf, BUFSIZE, 0);
    return string(buf, numRead);
}

StreamSocket::StreamSocket(StreamSocket&& other)
: fd{other.fd}, domain{other.domain}, protocol{other.protocol}, connected{other.connected},
  type{other.type}, port{other.port}, addr{other.addr}, peeraddr{other.peeraddr}, peername{std::move(other.peername)}
{
    other.fd = -1; 
}

StreamSocket& StreamSocket::operator=(StreamSocket&& other){
    if (this != &other){
        if (fd != -1)
            close(fd);
        fd = other.fd;
        domain = other.domain;
        protocol = other.protocol;
        connected = other.connected;
        type = other.type;
        port = other.port;
        addr = other.addr;
        peeraddr = other.peeraddr;
        peername = std::move(other.peername);
        other.fd = -1; 
    }
    return *this;
}

int StreamSocket::getpeerport() const{
    return ntohs(peeraddr.sin_port);
}

int StreamSocket::getport() const {
    return port;
}