#include "html_tree_test_win.h"

html_tree_test_win::html_tree_test_win(int _argc, char** _argv)
: html_tree_test(_argc, _argv) {

}

html_tree_test_win::~html_tree_test_win() {

}

void html_tree_test_win::init() {
    SetConsoleOutputCP(CP_UTF8);
}
