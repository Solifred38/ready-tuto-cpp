//===============================================
#include "GInclude.h"
//===============================================
template <typename T> T xMax(T x, T y) {
    return (x > y) ? x : y;
}
//===============================================
int main(int _argc, char** _argv) {
    std::cout << xMax<int>(3, 7) << std::endl;
    std::cout << xMax<double>(3.0, 7.0) << std::endl;
    std::cout << xMax<char>('g', 'e') << std::endl;
    return 0;
}
//===============================================
