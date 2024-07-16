#pragma once

#include "maj_db_sqlite_header.h"

class maj_db_sqlite_run;
class maj_db_sqlite_script;

class maj_db_sqlite_dao : public common_object {
    friend class maj_db_sqlite_run;
    friend class maj_db_sqlite_script;

private:
    maj_db_sqlite_dao();

public:
    ~maj_db_sqlite_dao();
    void initMaj();
    void runScript(const maj_db_sqlite_run& _obj);
    void runScript(const common_string& _code, const common_string& _filename, const common_string& _source);

private:
    bool isRunScript(const common_string& _code, const common_string& _filename);
    int insertScript(const common_string& _code, const common_string& _filename);

private:
    common_string m_dbRoot;
    common_string m_dbPath;
};
