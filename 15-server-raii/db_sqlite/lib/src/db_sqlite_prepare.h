#pragma once

#include "db_sqlite.h"

class db_sqlite_prepare : public common_object {
    friend class db_sqlite_run;

private:
    db_sqlite_prepare(sqlite3_stmt* _stmtSQL);

public:
    ~db_sqlite_prepare();
    void execQuery(const std::vector<s_db_sqlite_param>& _params, sqlite3* _dbSQL);
    int insertQuery(const std::vector<s_db_sqlite_param>& _params, sqlite3* _dbSQL);
    db_sqlite_rows readQuery(const std::vector<s_db_sqlite_param>& _params, sqlite3* _dbSQL);

private:
    void runBind(const std::vector<s_db_sqlite_param>& _params, sqlite3* _dbSQL);
    void bindNull(int _index, sqlite3* _dbSQL);
    void bindInt(int _index, int _data, sqlite3* _dbSQL);
    void bindDouble(int _index, double _data, sqlite3* _dbSQL);
    void bindText(int _index, const common_string& _data, sqlite3* _dbSQL);
    void bindBinary(int _index, const common_string& _data, sqlite3* _dbSQL);

private:
    sqlite3_stmt* m_stmtSQL;
};

