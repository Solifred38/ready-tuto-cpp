#include "html_tree_test.h"

int main(int _argc, char** _argv) {
    std::shared_ptr<html_tree_test> lProcess = html_tree_test::create(_argc, _argv);
    lProcess->run();
    return 0;
}
