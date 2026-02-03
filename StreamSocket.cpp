#include "StreamSocket.h"

StreamSocket::StreamSocket()
{
    this->fd = socket(AF_INET, SOCK_STREAM, 0);
    
}
