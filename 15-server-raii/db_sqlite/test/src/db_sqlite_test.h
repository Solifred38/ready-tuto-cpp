#pragma once

#include "db_sqlite_test_header.h"

class db_sqlite_test : public common_object {
protected:
    db_sqlite_test(int _argc, char** _argv);

public:
    ~db_sqlite_test();
    static std::shared_ptr<db_sqlite_test> create(int _argc, char** _argv);
    virtual void init() {}
    void run();

private:
    void runTest();

private:
    int m_argc;
    char** m_argv;
};
