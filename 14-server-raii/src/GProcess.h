//===============================================
#pragma once
//===============================================
#include "GObject.h"
//===============================================
class GProcess : public GObject {
protected:
    GProcess(int _argc, char** _argv);

public:
    ~GProcess();
    static std::shared_ptr<GProcess> create(int _argc, char** _argv);

public:
    void run();

private:
    virtual void initProcess();

protected:
    int m_argc;
    char** m_argv;
};
//===============================================
