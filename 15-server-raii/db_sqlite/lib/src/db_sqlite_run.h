
#pragma once

#include "db_sqlite.h"

class db_sqlite_run : public common_object {
public:
    db_sqlite_run(sqlite3* _dbSQL);
    ~db_sqlite_run();
    void execQuery(const common_string& _sql, const std::vector<s_db_sqlite_param>& _params);
    int insertQuery(const common_string& _sql, const std::vector<s_db_sqlite_param>& _params);
    db_sqlite_rows readQuery(const common_string& _sql, const std::vector<s_db_sqlite_param>& _params);
    void beginTransaction();
    void commitTransaction();

private:
    sqlite3* m_dbSQL;
};
