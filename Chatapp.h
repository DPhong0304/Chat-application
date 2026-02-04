#pragma once
#include <string>
#include <vector>
#include <map>
#include <iostream>
#include "StreamSocket.h"

int commandHandler(std::string& command, class Chatapp& app);
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
    void help();
    void myip();
    void myport();
    void connect(const std::string& ip, int port);  
    void list();
    void terminate(int connectionID);
    void send(int connectionID, const std::string& message);
    void exit();
    friend int commandHandler(std::string& command, Chatapp& app);
    // friend void connectionHandler(const std::string& message);
};

