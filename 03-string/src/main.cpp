//===============================================
#include "GString.h"
//===============================================
int main(int _argc, char** _argv) {
    GString lData = "Bonjour tout le monde.";
    std::cout << lData << std::endl;
    GString lData2 = lData;
    std::cout << lData2 << std::endl;
    lData2 = lData;
    std::cout << lData2 << std::endl;
    lData2 = lData2 + " - " + lData;
    std::cout << lData2 << std::endl;
    lData2 = "|data=" + lData2 + " - " + lData;
    std::cout << lData2 << std::endl;
    return 0;
}
//===============================================
