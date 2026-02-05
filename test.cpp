#include <ifaddrs.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <string>
#include <iostream>

using namespace std;

std::string get_lan_ip() {
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
            std::string ip = inet_ntoa(sa->sin_addr);

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

int 
main(void){
    cout << get_lan_ip() << endl;
    return 0;
}
