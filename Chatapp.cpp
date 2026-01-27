#include <string>
#include "StreamSocket.h"
#include "Chatapp.h"

Chatapp::Chatapp(int& port)
    : Chatapp, listenSocket{StreamSocket{port}}
{
}