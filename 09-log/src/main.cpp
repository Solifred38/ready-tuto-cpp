//===============================================
#include "GLog.h"
//===============================================
int main(int _argc, char** _argv) {
    GLog slog;
    std::string lData = "ReadyDev";
    slog(eGERR, "Bonjour tout le monde."
    "|data=%s", lData.c_str());
    return 0;
}
//===============================================
