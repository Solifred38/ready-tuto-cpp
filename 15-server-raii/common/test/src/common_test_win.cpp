#include "common_test_win.h"

common_test_win::common_test_win(int _argc, char** _argv)
: common_test(_argc, _argv) {

}

common_test_win::~common_test_win() {

}

void common_test_win::init() {
    SetConsoleOutputCP(CP_UTF8);
}
