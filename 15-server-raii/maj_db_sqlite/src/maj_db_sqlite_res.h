#pragma once

#include "maj_db_sqlite_header.h"

class maj_db_sqlite_res : public common_object {
    friend class maj_db_sqlite;

private:
    maj_db_sqlite_res();

public:
    ~maj_db_sqlite_res();
    void run();

private:
    common_string m_resRoot;
    common_string m_resPath;
};
