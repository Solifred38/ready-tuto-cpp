//===============================================
#include "GServer.h"
//===============================================
int main(int _argc, char** _argv) {
    SetConsoleOutputCP(CP_UTF8);
    GSocket* lServer = GSocket::Create();
    lServer->run();
    delete lServer;
    return 0;
}
//===============================================
