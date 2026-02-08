#include "StreamSocket.h"

using namespace std;


int main(void){
    StreamSocket newsocket{};
    newsocket.SSconnect("192.168.1.18", 1234);
    string mesg = "hello from client";
    newsocket.SSsend(mesg);   
    return 0;
}