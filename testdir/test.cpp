#include "../StreamSocket.h"
#include "../Chatapp.h"
#include <iostream>

using namespace std;


int main(){
    StreamSocket newsocket{};
    string ip = get_lan_ip();
    newsocket.SSconnect(ip, 1234);
    string mesg = "test_client";
    newsocket.SSsend(mesg);   
    while (true) {
        cout << "input your message: " << flush;
        if (!std::getline(cin, mesg)) break;   // EOF or error
        if (mesg.empty()) continue;            // ignore empty lines
        newsocket.SSsend(mesg);
    }
    return 0;
}