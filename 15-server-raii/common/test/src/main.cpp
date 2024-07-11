#include "common_test.h"

int main(int _argc, char** _argv) {
    std::shared_ptr<common_test> lProcess = common_test::create(_argc, _argv);
    lProcess->run();
    return 0;
}
