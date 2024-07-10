//===============================================
#include "GProcess.h"
//===============================================
int main(int _argc, char** _argv) {
    std::shared_ptr<GProcess> lProcess = GProcess::create(_argc, _argv);
    lProcess->run();
    return 0;
}
//===============================================
