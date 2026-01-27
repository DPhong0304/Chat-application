#pragma once
#include <string>
#include <vector>
#include "StreamSocket.h"

// typedef void (*Operation)(vector<std::string> arguments);

class Chatapp {
private:
    StreamSocket listenSocket;     
    std::vector<StreamSocket> connectionList;
    // map<std::string, Operation> cmdHandler;

public:
    Chatapp();
    Chatapp(int& port);  
    void run(); 
    void help();
    void myip();
    void myport();
    void connect(const std::string& ip, int port);  
    void list();
    void terminate(int connectionID);
    void send(int connectionID, const std::string& message);
    void exit();
    ~Chatapp();
};