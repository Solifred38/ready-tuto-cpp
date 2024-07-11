#pragma once

#include "common_test_header.h"

class common_test : public common_object {
protected:
    common_test(int _argc, char** _argv);

public:
    ~common_test();
    static std::shared_ptr<common_test> create(int _argc, char** _argv);
    virtual void init() {}
    void run();

private:
    void runString();
    void runLog();

private:
    int m_argc;
    char** m_argv;
};
