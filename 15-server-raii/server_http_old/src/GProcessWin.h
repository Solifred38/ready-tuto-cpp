//===============================================
#if defined(_WIN32)
//===============================================
#pragma once
//===============================================
#include "GProcess.h"
//===============================================
class GProcessWin : public GProcess {
    friend class GProcess;

private:
    GProcessWin(int _argc, char** _argv);

public:
    ~GProcessWin();

private:
    void initProcess();
};
//===============================================
#endif
//===============================================
