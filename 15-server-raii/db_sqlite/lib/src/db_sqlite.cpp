
#include "db_sqlite.h"
#include "db_sqlite_run.h"

db_sqlite::db_sqlite()
: m_dbRoot  ("../web")
, m_dbPath  ("/private/test/sqlite/test.dat") {

}

db_sqlite::db_sqlite(const common_string& _dbPath)
: m_dbRoot  ("../web")
, m_dbPath  (_dbPath) {

}
db_sqlite::db_sqlite(const common_string& _dbRoot, const common_string& _dbPath)
: m_dbRoot  (_dbRoot)
, m_dbPath  (_dbPath) {

}

db_sqlite::~db_sqlite() {

}

sqlite3* db_sqlite::open() {
    sqlite3* dbSQL = 0;
    common_string dbPath = m_dbRoot + m_dbPath;

    int lResult = sqlite3_open(dbPath.c_str(), &dbSQL);

    if(lResult != SQLITE_OK) {
        slog(eGERR, "L'initialisation de SQLITE a échoué."
        "|codeErreur=%d"
        "|msgErreur=%s", sqlite3_errcode(dbSQL), sqlite3_errmsg(dbSQL));
        m_errors.addProblem();
        return 0;
    }

    return dbSQL;
}

void db_sqlite::execQuery(const common_string& _sql) {
    sqlite3* dbSQL = 0;
    common_string dbPath = m_dbRoot + m_dbPath;

    int lResult = sqlite3_open(dbPath.c_str(), &dbSQL);

    if(lResult != SQLITE_OK) {
        slog(eGERR, "L'initialisation de SQLITE a échoué."
        "|codeErreur=%d"
        "|msgErreur=%s"
        "|requeteSQL=%s", sqlite3_errcode(dbSQL), sqlite3_errmsg(dbSQL), _sql.c_str());
        m_errors.addProblem();
        return;
    }

    db_sqlite_run dbRun(dbSQL);
    dbRun.execQuery(_sql, m_params);
    m_errors.addErrors(dbRun.getErrors());
}

int db_sqlite::insertQuery(const common_string& _sql) {
    sqlite3* dbSQL = 0;
    common_string dbPath = m_dbRoot + m_dbPath;

    int lResult = sqlite3_open(dbPath.c_str(), &dbSQL);

    if(lResult != SQLITE_OK) {
        slog(eGERR, "L'initialisation de SQLITE a échoué."
        "|codeErreur=%d"
        "|msgErreur=%s"
        "|requeteSQL=%s", sqlite3_errcode(dbSQL), sqlite3_errmsg(dbSQL), _sql.c_str());
        m_errors.addProblem();
        return 0;
    }

    db_sqlite_run dbRun(dbSQL);
    int lInsertId = dbRun.insertQuery(_sql, m_params);
    m_errors.addErrors(dbRun.getErrors());
    return lInsertId;
}

db_sqlite_rows db_sqlite::readQuery(const common_string& _sql) {
    sqlite3* dbSQL = 0;
    common_string dbPath = m_dbRoot + m_dbPath;

    int lResult = sqlite3_open(dbPath.c_str(), &dbSQL);

    if(lResult != SQLITE_OK) {
        slog(eGERR, "L'initialisation de SQLITE a échoué."
        "|codeErreur=%d"
        "|msgErreur=%s"
        "|requeteSQL=%s", sqlite3_errcode(dbSQL), sqlite3_errmsg(dbSQL), _sql.c_str());
        m_errors.addProblem();
        return db_sqlite_rows();
    }

    db_sqlite_run dbRun(dbSQL);
    db_sqlite_rows lRows = dbRun.readQuery(_sql, m_params);
    m_errors.addErrors(dbRun.getErrors());
    return lRows;
}

void db_sqlite::bindNull(int _index) {
    s_db_sqlite_param lParam;
    lParam.m_type = SQLITE_NULL;
    lParam.m_index = _index;
    m_params.push_back(lParam);
}

void db_sqlite::bindInt(int _index, int _data) {
    s_db_sqlite_param lParam;
    lParam.m_type = SQLITE_INTEGER;
    lParam.m_index = _index;
    lParam.m_dataInt = _data;
    m_params.push_back(lParam);
}

void db_sqlite::bindDouble(int _index, double _data) {
    s_db_sqlite_param lParam;
    lParam.m_type = SQLITE_FLOAT;
    lParam.m_index = _index;
    lParam.m_dataDouble = _data;
    m_params.push_back(lParam);
}

void db_sqlite::bindText(int _index, const common_string& _data) {
    s_db_sqlite_param lParam;
    lParam.m_type = SQLITE_TEXT;
    lParam.m_index = _index;
    lParam.m_dataText = _data;
    m_params.push_back(lParam);
}

void db_sqlite::bindBinary(int _index, const common_string& _data) {
    s_db_sqlite_param lParam;
    lParam.m_type = SQLITE_BLOB;
    lParam.m_index = _index;
    lParam.m_dataText = _data;
    m_params.push_back(lParam);
}


