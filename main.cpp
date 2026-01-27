#include <iostream>
#include <string>
#include "Chatapp.h"

using namespace std;

int main(int argc, char* argv[]){
    Chatapp app(argc, argv);
    app.cmdInterface();
    return 0;
}