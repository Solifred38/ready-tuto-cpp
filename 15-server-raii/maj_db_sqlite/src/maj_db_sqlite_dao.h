#pragma once

#include "maj_db_sqlite_header.h"

class maj_db_sqlite_run;

class maj_db_sqlite_dao : public common_object {
    friend class maj_db_sqlite_run;

private:
    maj_db_sqlite_dao();

public:
    ~maj_db_sqlite_dao();
    void initMaj();
    void runScript(const maj_db_sqlite_run& _obj);

private:
    bool isRunScript(const maj_db_sqlite_run& _obj);
    int insertScript(const maj_db_sqlite_run& _obj);

private:
    common_string m_dbRoot;
    common_string m_dbPath;
};
