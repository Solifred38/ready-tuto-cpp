#pragma once

#include "maj_db_sqlite_header.h"

class maj_db_sqlite : public common_object {
protected:
    maj_db_sqlite(int _argc, char** _argv);

public:
    ~maj_db_sqlite();
    static std::shared_ptr<maj_db_sqlite> create(int _argc, char** _argv);
    virtual void init() {}
    void run();

private:
    int m_argc;
    char** m_argv;
};
