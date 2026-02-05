#pragma once
#include <string>
#include <vector>
#include <map>
#include <iostream>
#include "StreamSocket.h"
#include <sstream>
#include <ifaddrs.h>
#include <arpa/inet.h>


int commandHandler(std::string& command, class Chatapp& app);
std::string get_lan_ip();
// void connectionHandler(const std::string& message);

class Chatapp {
private:
    StreamSocket listenSocket;     
    std::vector<StreamSocket> connectionList;
    char hostip[INET_ADDRSTRLEN];
    int port;
    std::string username;
    Chatapp();

public:
    Chatapp(const int& argc, char* argv[]); 
    ~Chatapp();
    void cmdInterface(); 
    void appHelp();
    void myip();
    void myport();
    void appConnect(const std::string& remoteip, int remoteport);  
    void appList();
    void appTerminate(int connectionID);
    void appSend(int connectionID, std::string& message);
    void appExit();
    bool isValidConnID(int connectionID);
    friend int commandHandler(std::string& command, Chatapp& app);
    // friend void connectionHandler(const std::string& message);
};
