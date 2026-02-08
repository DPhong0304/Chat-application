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

void StreamSocket::SSconnect(const std::string& ipaddr, int port){
    memset(&peeraddr, 0, sizeof(Address));
    peeraddr.sin_family = domain;
    inet_pton(domain, ipaddr.c_str(), &(peeraddr.sin_addr));
    peeraddr.sin_port = htons(port);
    connect(fd, (sockaddr*) &peeraddr, sizeof(Address));
    cout << "Connected to " << ipaddr << " on port " << port << endl;
}

StreamSocket::StreamSocket(int fd, Address peeraddr, string& peername)
: fd{fd}, peeraddr{peeraddr}, peername{peername}
{
}

StreamSocket StreamSocket::SSaccept() {
    socklen_t len = sizeof(peeraddr);
    int connfd = accept(fd, (sockaddr*)&peeraddr, &len);
    // char buff[NAMELEN];
    // recv(connfd, buff, sizeof(buff), 0);
    // peername = string(buff);
    // cout << "Accepted connection from " << peername << endl;
    peername = "??????"; 
    return StreamSocket(connfd, peeraddr, peername);
}

// StreamSocket StreamSocket::SSaccept() {
//     socklen_t len = sizeof(peeraddr);
//     int connfd = accept(fd, (sockaddr*)&peeraddr, &len);
//     if (connfd < 0) {
//         perror("accept");
//         return StreamSocket{}; // or throw
//     }

//     char buff[NAMELEN];
//     ssize_t n = recv(connfd, buff, sizeof(buff), 0);
//     if (n <= 0) {
//         if (n < 0) perror("recv(username)");
//         // close and return something invalid, or handle better
//         close(connfd);
//         return StreamSocket{};
//     }

//     std::string pname(buff, (size_t)n);
//     // optional: trim newline/spaces
//     while (!pname.empty() && (pname.back() == '\n' || pname.back() == '\r' || pname.back() == ' '))
//         pname.pop_back();

//     std::string passed_name = pname;
//     cout << "Accepted connection from " << passed_name << endl;
//     return StreamSocket(connfd, peeraddr, passed_name);
// }


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

// std::string StreamSocket::SSrecv() {
//     char buf[BUFSIZE];

//     ssize_t n = recv(fd, buf, sizeof(buf), 0);
//     if (n > 0) {
//         return std::string(buf, (size_t)n);
//     }
//     if (n == 0) {
//         // peer closed cleanly
//         return ""; // use empty to mean "disconnected"
//     }

//     // n < 0
//     if (errno == EINTR) return "";          // interrupted, try again in caller
//     if (errno == EAGAIN || errno == EWOULDBLOCK) return ""; // if nonblocking later

//     // real error
//     perror("recv");
//     return "";
// }


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