#include "StreamSocket.h"

using namespace std;

StreamSocket::StreamSocket(){
    fd = socket(protocol, type, protocol);
}
 
StreamSocket::StreamSocket(int port, const string& ipaddr)
: StreamSocket(), domain(AF_INET), protocol(0), connected(false),
type(SOCK_STREAM), port(port)
{
    memset(&addr, 0, sizeof(Address));
    addr.sin_family = domain;
    inet_pton(domain, ipaddr.c_str(), &(addr.sin_addr));
    addr.sin_port = htons(port);
    bind(fd, (sockaddr*) &addr, sizeof(Address));
}

StreamSocket::StreamSocket(int fd)
: fd(fd)
{
}

void StreamSocket::SSconnect(const std::string& ipaddr, int port){
    Address remoteaddr;
    memset(&remoteaddr, 0, sizeof(Address));
    remoteaddr.sin_family = domain;
    inet_pton(domain, ipaddr.c_str(), &(remoteaddr.sin_addr));
    remoteaddr.sin_port = htons(port);
    connect(fd, (sockaddr*) &remoteaddr, sizeof(Address));
}

void StreamSocket::SSlisten(int backlog){

}
