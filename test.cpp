#include "StreamSocket.h"
#include <iostream>

using namespace std;


int main(){
    StreamSocket newsocket{};
    newsocket.SSconnect("192.168.1.18", 1234);
    string mesg = "hello from client";
    newsocket.SSsend(mesg);   
    while (true) {
        cout << "input your message: " << flush;
        if (!std::getline(cin, mesg)) break;   // EOF or error
        if (mesg.empty()) continue;            // ignore empty lines
        newsocket.SSsend(mesg);
    }
    return 0;
}