//===============================================
#include "GSQLite.h"
#include "GSQLiteRun.h"
//===============================================
GSQLite::GSQLite()
: m_dbRoot      ("../web")
, m_filename    ("/private/test/sqlite/test.dat") {

}
//===============================================
GSQLite::GSQLite(const GString& _filename)
: m_dbRoot      ("../web")
, m_filename    (_filename) {

}
//===============================================
GSQLite::~GSQLite() {

}
//===============================================
void GSQLite::execQuery(const GString& _sql) {
    sqlite3* dbSQL = 0;
    GString dbPath = m_dbRoot + m_filename;

    int isOK = sqlite3_open(dbPath.c_str(), &dbSQL);

    if(isOK != SQLITE_OK) {
        slog(eGERR, "L'initialisation de SQLITE a échoué."
        "|codeErreur=%d"
        "|msgErreur=%s", sqlite3_errcode(dbSQL), sqlite3_errmsg(dbSQL));
        m_errors.addProblem();
        return;
    }

    GSQLiteRun dbRun(dbSQL);
    dbRun.execQuery(_sql);
    m_errors.addErrors(dbRun.getErrors());
}
//===============================================
void GSQLite::prepareQuery(const GString& _sql) {
    sqlite3* dbSQL = 0;
    GString dbPath = m_dbRoot + m_filename;

    int isOK = sqlite3_open(dbPath.c_str(), &dbSQL);

    if(isOK != SQLITE_OK) {
        slog(eGERR, "L'initialisation de SQLITE a échoué."
        "|codeErreur=%d"
        "|msgErreur=%s", sqlite3_errcode(dbSQL), sqlite3_errmsg(dbSQL));
        m_errors.addProblem();
        return;
    }

    GSQLiteRun dbRun(dbSQL);
    dbRun.prepareQuery(_sql, m_params);
    m_errors.addErrors(dbRun.getErrors());
}
//===============================================
void GSQLite::bindNull(int _index) {
    sGSQLiteParam lParam;
    lParam.m_type = eGSQLiteParam::DATA_NULL;
    lParam.m_index = _index;
    m_params.push_back(lParam);
}
//===============================================
void GSQLite::bindInt(int _index, int _data) {
    sGSQLiteParam lParam;
    lParam.m_type = eGSQLiteParam::DATA_INT;
    lParam.m_index = _index;
    lParam.m_dataInt = _data;
    m_params.push_back(lParam);
}
//===============================================
void GSQLite::bindDouble(int _index, double _data) {
    sGSQLiteParam lParam;
    lParam.m_type = eGSQLiteParam::DATA_DOUBLE;
    lParam.m_index = _index;
    lParam.m_dataDouble = _data;
    m_params.push_back(lParam);
}
//===============================================
void GSQLite::bindText(int _index, const GString& _data) {
    sGSQLiteParam lParam;
    lParam.m_type = eGSQLiteParam::DATA_TEXT;
    lParam.m_index = _index;
    lParam.m_dataText = _data;
    m_params.push_back(lParam);
}
//===============================================
void GSQLite::bindBinary(int _index, const GString& _data) {
    sGSQLiteParam lParam;
    lParam.m_type = eGSQLiteParam::DATA_BINARY;
    lParam.m_index = _index;
    lParam.m_dataText = _data;
    m_params.push_back(lParam);
}
//===============================================

