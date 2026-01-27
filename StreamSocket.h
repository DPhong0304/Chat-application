#pragma once

class StreamSocket{
private:
    int fd;
    int domain;
    int protocol;
    bool connected;
public:
    StreamSocket();
    StreamSocket(int domain);
};
