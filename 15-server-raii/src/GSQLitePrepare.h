//===============================================
#pragma once
//===============================================
#include "GSQLite.h"
//===============================================
class GSQLitePrepare : public GObject {
    friend class GSQLiteRun;

private:
    GSQLitePrepare(sqlite3_stmt* _stmtSQL);

public:
    ~GSQLitePrepare();
    void run(const std::vector<sGSQLiteParam>& _params, sqlite3* _dbSQL);

private:
    void bindNull(int _index, sqlite3* _dbSQL);
    void bindInt(int _index, int _data, sqlite3* _dbSQL);
    void bindDouble(int _index, double _data, sqlite3* _dbSQL);
    void bindText(int _index, const GString& _data, sqlite3* _dbSQL);
    void bindBinary(int _index, const GString& _data, sqlite3* _dbSQL);

private:
    sqlite3_stmt* m_stmtSQL;
};
//===============================================
