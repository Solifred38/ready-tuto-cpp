//===============================================
#include "GInclude.h"
//===============================================
int main(int _argc, char** _argv) {
#if defined(_WIN32)
    std::cout << "Je suis sur un système WINDOWS." << std::endl;
#elif defined(__linux__)
    std::cout << "Je suis sur un système WINDOWS." << std::endl;
#endif
    return 0;
}
//===============================================
