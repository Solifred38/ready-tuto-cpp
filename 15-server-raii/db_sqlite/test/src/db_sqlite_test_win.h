#pragma once

#include "db_sqlite_test.h"

class db_sqlite_test_win : public db_sqlite_test {
    friend class db_sqlite_test;

private:
    db_sqlite_test_win(int _argc, char** _argv);

public:
    ~db_sqlite_test_win();
    void init();
};
