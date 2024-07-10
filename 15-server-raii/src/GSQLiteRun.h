//===============================================
#pragma once
//===============================================
#include "GSQLite.h"
//===============================================
class GSQLiteRun : public GObject {
    friend class GSQLite;

private:
    GSQLiteRun(sqlite3* _dbSQL);

public:
    ~GSQLiteRun();
    void execQuery(const GString& _sql);
    void prepareQuery(const GString& _sql, const std::vector<sGSQLiteParam>& _params);

private:
    sqlite3* m_dbSQL;
};
//===============================================
