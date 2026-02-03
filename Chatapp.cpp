// #include "StreamSocket.h"
#include "Chatapp.h"
#include <unistd.h>

using namespace std;
int loop = 0;


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
            cout << "Please input valid port for this application: ";
            cin >> this->port;
        }
    }
    else{
        this->port = stoi(argv[1]);
    }

    this->username = "kittykitty";

    // while (this->username.empty()){
    //     cout << "Enter your username: ";    
    //     getline(cin, this->username);
    //     this->username.erase(0, this->username.find_first_not_of(" \t")); 
    // }
}

void Chatapp::cmdInterface(){
    string command;
    fd_set readfds;
    int readynum, nfds = 3;

    while (1){
        cout << loop << this->username << "@chatapp> ";
        cout.flush();
        FD_ZERO(&readfds); 
        FD_SET(STDIN_FILENO, &readfds);
        if (select(nfds, &readfds, NULL, NULL, NULL) == -1){
            cerr << "select error!" << endl;
        }
        
        if (FD_ISSET(STDIN_FILENO, &readfds)){
            if (commandHandler(command, *this) == -1){
                cerr << "command error!" << endl;
            }
        }
        loop++;
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
    cout.flush();
    std::exit(0);
}

int commandHandler(std::string& command, Chatapp& app){
    getline(cin, command);
    command.erase(0, command.find_first_not_of(" \t")); 

    if (command.empty()) { 
        return 0;
    }
    if (command == "help"){
        app.help();
    }
    else if (command == "myip"){
        app.myip();
    }
    else if (command == "myport"){
        app.myport();
    }
    else if (command == "connect"){
        return -1;
    }
    else if (command == "list"){
        app.list();
    }
    else if (command == "terminate"){
        return -1;
    }
    else if (command == "send"){
        return -1;
    }
    else if (command == "exit"){
        app.exit();
    }
    else{
        cout << "Invalid command. Type 'help' to see the list of commands." << endl;
    }
    return 0;

}