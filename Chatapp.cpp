// #include "StreamSocket.h"
#include "Chatapp.h"

using namespace std;

bool is_valid_port(int port) {
    return port >= 1 && port <= 65535;
}

Chatapp::Chatapp(){
    printf("Chat application started!\n");
    this->port = -1;
}

Chatapp::Chatapp(const int& argc, char* argv[])
: Chatapp{} 
{
    if (argc < 2){
        while (!is_valid_port(this->port)){
            cout << "Please input valid port for this application: " << endl;
            cin >> this->port;
        }
    }
    else{
        this->port = stoi(argv[1]);
    }
}

void Chatapp::cmdInterface(){
    string command;
    while (1){
        cin >> command;
        if (command == "help"){
            this->help();
        }
        else if (command == "myip"){
            this->myip();
        }
        else if (command == "myport"){
            this->myport();
        }
        else if (command == "connect"){
            continue;
        }
        else if (command == "list"){
            continue;
        }
        else if (command == "terminate"){
            continue;
        }
        else if (command == "send"){
            continue;
        }
        else if (command == "exit"){
            this->exit();
        }
        else{#include <iostream>
            cout << "Invalid command. Type 'help' to see the list of commands." << endl;
        }
    }
}

void Chatapp::help(){
    cout << "help                               - Displays all the commands supported by this chat application" << endl;
    cout << "myip                               - Displays the IP address of this process" << endl;
    cout << "myport                             - Displays the port on which this process is listening for incoming connections" << endl;
    cout << "connect <destination> <port no>    - Establishes a new connection to the specified <destination> at the specified <port no>" << endl;
    cout << "list                               - Displays a numbered list of all the connections this process is part of" << endl;
    cout << "terminate <connection id>          - Terminates the connection listed under the specified <connection id>" << endl;
    cout << "send <connection id> <message>     - Sends a message to the host on the connection listed under the specified <connection id>" << endl;
    cout << "exit                               - Closes all connections and terminates this process" << endl;
};

void Chatapp::myip(){
    cout << "My IP address is: " << endl;
}

void Chatapp::myport(){
    cout << "My port number is: " << this->port << endl;
}

void Chatapp::connect(const std::string& ip, int port){
    
}

void Chatapp::list(){
    
}

void Chatapp::terminate(int connectionID){
    
}

void Chatapp::send(int connectionID, const std::string& message){
    
}

void Chatapp::exit(){
    cout << "Exiting chat application..." << endl;
    std::exit(0);
}