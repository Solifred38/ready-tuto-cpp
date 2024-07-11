#pragma once

#include "common_test.h"

class common_test_win : public common_test {
    friend class common_test;

private:
    common_test_win(int _argc, char** _argv);

public:
    ~common_test_win();
    void init();
};
