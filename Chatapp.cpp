// #include "StreamSocket.h"
#include "Chatapp.h"
#include <unistd.h>
#define MAX(a, b) ((a) > (b) ? (a) : (b))

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
    hostip = get_lan_ip();
    // input port
    if (argc < 2){
        while (!is_valid_port(this->port)){
            cout << "Please input valid port for this application: ";
            cin >> this->port;
        }
    }
    else{
        this->port = stoi(argv[1]);
    }

    // input username 
    while (this->username.empty()){
        cout << "Enter your username: ";    
        getline(cin, this->username);
        this->username.erase(0, this->username.find_first_not_of(" \t")); 
    }

    // setup listening socket
    listenSocket = StreamSocket{port, "0.0.0.0"};
    listenSocket.SSlisten(SOMAXCONN);
}

Chatapp::~Chatapp() = default;

void Chatapp::cmdInterface(){
    string command;
    string inMesg;
    fd_set readfds;
    int readynum, nfds = listenSocket.getfd() + 1;

    while (1){
        cout << username << "@chatapp> ";
        cout.flush();

        // fd set
        FD_ZERO(&readfds); 
        FD_SET(STDIN_FILENO, &readfds);
        FD_SET(listenSocket.getfd(), &readfds);
        for (auto& socket : connectionList){
            FD_SET(socket.getfd(), &readfds);
        }

        if (select(nfds, &readfds, nullptr, nullptr, nullptr) == -1){
            cerr << "select error!" << endl;
        }
        
        // command processing stdin
        if (FD_ISSET(STDIN_FILENO, &readfds)){
            if (commandHandler(command, *this) == -1){
                cerr << "command error!" << endl;
            }
        }

        // new connection
        if (FD_ISSET(listenSocket.getfd(), &readfds)){
            connectionList.emplace_back(listenSocket.SSaccept());
            nfds = MAX(connectionList.back().getfd() + 1, nfds);
        }

        // message income
        for (auto& socket : connectionList){
            if (FD_ISSET(socket.getfd(), &readfds)){
                inMesg = socket.SSrecv();
                cout << "From " << socket.getpeername() << ": "<< inMesg <<endl;
            }
        }
    }
}

void Chatapp::appHelp(){
    cout << "help                               - Displays all the commands supported by this chat application" << endl;
    cout << "myip                               - Displays the IP address of this process" << endl;
    cout << "myport                             - Displays the port on which this process is listening for incoming connections" << endl;
    cout << "connect <destination> <port no>    - Establishes a new connection to the specified <destination> at the specified <port no>" << endl;
    cout << "list                               - Displays a numbered list of all the connections this process is part of" << endl;
    cout << "terminate <connection id>          - Terminates the connection listed under the specified <connection id>" << endl;
    cout << "send <connection id> <message>     - Sends a message to the host on the connection listed under the specified <connection id>" << endl;
    cout << "exit                               - Closes all connections and terminates this process" << endl;
};

string get_lan_ip() {
    struct ifaddrs *ifaddr, *ifa;

    if (getifaddrs(&ifaddr) == -1) {
        return "";
    }

    for (ifa = ifaddr; ifa != nullptr; ifa = ifa->ifa_next) {
        if (!ifa->ifa_addr)
            continue;

        // IPv4 only
        if (ifa->ifa_addr->sa_family == AF_INET) {
            auto *sa = (struct sockaddr_in *)ifa->ifa_addr;
            char ip_str[INET_ADDRSTRLEN];
            inet_ntop(AF_INET, &sa->sin_addr, ip_str, INET_ADDRSTRLEN);
            std::string ip = ip_str;

            // skip loopback
            if (ip != "127.0.0.1") {
                freeifaddrs(ifaddr);
                return ip;
            }
        }
    }

    freeifaddrs(ifaddr);
    return "";
}

void Chatapp::myip(){
    if (hostip.empty()){
        cout << "Cannot query ip! Try again" << endl;
        hostip = get_lan_ip();
        return;
    }
    cout << "My ip address is: " << hostip << endl;
}

void Chatapp::myport(){
    cout << "My port number is: " << this->port << endl;
}

void Chatapp::appConnect(const std::string& remoteip, int remoteport){
    StreamSocket newSocket{};
    newSocket.SSconnect(remoteip, remoteport);
    newSocket.SSsend(username);
    connectionList.emplace_back(newSocket);
}

void Chatapp::appList(){
    cout << "ConnID" << "fd" << "hostname" << "ip" << endl;
    int connid = 0;
    string peerip;
    for (auto& socket : connectionList){
        connid++;
        peerip = socket.getpeerip_P();
        cout << connid << socket.getfd() << socket.getpeername() << socket.getpeerip_P()<< endl;
    }
}

void Chatapp::appTerminate(int connectionID){
    if (!isValidConnID(connectionID)){
        cout << "The connection ID " << connectionID <<" is not identified! Type \"list\" for more information about connetion ID" << endl;
        return;
    }
    connectionList.erase(connectionList.begin() + connectionID - 1);    
}

void Chatapp::appSend(int connectionID, std::string& message){
    if (!isValidConnID(connectionID)){
        cout << "The connection ID " << connectionID <<" is not identified! Type \"list\" for more information about connetion ID" << endl;
        return;
    }
    connectionList[connectionID - 1].SSsend(message);
}

void Chatapp::appExit(){
    cout << "Exiting chat application..." << endl;
    cout.flush();
    std::exit(0);
}

vector<string> split(const string& s) {
    istringstream iss(s);
    vector<std::string> tokens;
    string token;

    while (iss >> token) {      
        tokens.push_back(token);
    }
    return tokens;
}

int commandHandler(std::string& command, Chatapp& app){
    getline(cin, command);
    command.erase(0, command.find_first_not_of(" \t")); 
    
    if (command.empty()) { 
        return 0;
    }

    vector<string> args{split(command)};

    if (args[0] == "help"){
        app.appHelp();
    }
    else if (args[0] == "myip"){
        app.myip();
    }
    else if (args[0] == "myport"){
        app.myport();
    }
    else if (args[0] == "connect"){
        if (args.size() < 3) return -1;
        app.appConnect(args[1], stoi(args[2]));
    }
    else if (args[0] == "list"){ 
        app.appList();
    }
    else if (args[0] == "terminate"){
        if (args.size() < 2) return -1;
        app.appTerminate(stoi(args[1]));
    }
    else if (args[0] == "send"){
        if (args.size() < 3) return -1;
        app.appSend(stoi(args[1]), args[2]);
    }
    else if (args[0] == "exit"){
        app.appExit();
    }
    else{
        cout << "Command \"" << args[0] << "\"not found. Type 'help' to see the list of commands." << endl;
    }
    return 0;

}

bool Chatapp::isValidConnID(int connID){
    return connID >= 1 && connID <= connectionList.size();
}