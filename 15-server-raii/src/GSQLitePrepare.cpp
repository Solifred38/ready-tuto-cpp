//===============================================
#include "GSQLitePrepare.h"
//===============================================
GSQLitePrepare::GSQLitePrepare(sqlite3_stmt* _stmtSQL)
: m_stmtSQL (_stmtSQL) {

}
//===============================================
GSQLitePrepare::~GSQLitePrepare() {
    sqlite3_finalize(m_stmtSQL);
}
//===============================================
void GSQLitePrepare::run(const std::vector<sGSQLiteParam>& _params, sqlite3* _dbSQL) {
    std::vector<sGSQLiteParam>::const_iterator it;
    for(it = _params.begin(); it != _params.end(); ++it) {
        sGSQLiteParam lParam = *it;
        if(lParam.m_type == eGSQLiteParam::DATA_NULL) {
            bindNull(lParam.m_index, _dbSQL);
        }
        else if(lParam.m_type == eGSQLiteParam::DATA_INT) {
            bindInt(lParam.m_index, lParam.m_dataInt, _dbSQL);
        }
        else if(lParam.m_type == eGSQLiteParam::DATA_DOUBLE) {
            bindDouble(lParam.m_index, lParam.m_dataDouble, _dbSQL);
        }
        else if(lParam.m_type == eGSQLiteParam::DATA_TEXT) {
            bindText(lParam.m_index, lParam.m_dataText, _dbSQL);
        }
        else if(lParam.m_type == eGSQLiteParam::DATA_BINARY) {
            bindBinary(lParam.m_index, lParam.m_dataText, _dbSQL);
        }
    }
}
//===============================================
void GSQLitePrepare::bindNull(int _index, sqlite3* _dbSQL) {
    int isOK = sqlite3_bind_null(m_stmtSQL, _index);

    if(isOK != SQLITE_OK) {
        slog(eGERR, "La liaison des paramètres de la requête SQLITE a échoué."
        "|codeErreur=%d"
        "|msgErreur=%s", sqlite3_errcode(_dbSQL), sqlite3_errmsg(_dbSQL));
        m_errors.addProblem();
        return;
    }
}
//===============================================
void GSQLitePrepare::bindInt(int _index, int _data, sqlite3* _dbSQL) {
    int isOK = sqlite3_bind_int(m_stmtSQL, _index, _data);

    if(isOK != SQLITE_OK) {
        slog(eGERR, "La liaison des paramètres de la requête SQLITE a échoué."
        "|codeErreur=%d"
        "|msgErreur=%s", sqlite3_errcode(_dbSQL), sqlite3_errmsg(_dbSQL));
        m_errors.addProblem();
        return;
    }
}
//===============================================
void GSQLitePrepare::bindDouble(int _index, double _data, sqlite3* _dbSQL) {
    int isOK = sqlite3_bind_double(m_stmtSQL, _index, _data);

    if(isOK != SQLITE_OK) {
        slog(eGERR, "La liaison des paramètres de la requête SQLITE a échoué."
        "|codeErreur=%d"
        "|msgErreur=%s", sqlite3_errcode(_dbSQL), sqlite3_errmsg(_dbSQL));
        m_errors.addProblem();
        return;
    }
}
//===============================================
void GSQLitePrepare::bindText(int _index, const GString& _data, sqlite3* _dbSQL) {
    int isOK = sqlite3_bind_text(m_stmtSQL, _index, _data.c_str(), _data.size(), NULL);

    if(isOK != SQLITE_OK) {
        slog(eGERR, "La liaison des paramètres de la requête SQLITE a échoué."
        "|codeErreur=%d"
        "|msgErreur=%s", sqlite3_errcode(_dbSQL), sqlite3_errmsg(_dbSQL));
        m_errors.addProblem();
        return;
    }
}
//===============================================
void GSQLitePrepare::bindBinary(int _index, const GString& _data, sqlite3* _dbSQL) {
    int isOK = sqlite3_bind_blob(m_stmtSQL, _index, _data.c_str(), _data.size(), NULL);

    if(isOK != SQLITE_OK) {
        slog(eGERR, "La liaison des paramètres de la requête SQLITE a échoué."
        "|codeErreur=%d"
        "|msgErreur=%s", sqlite3_errcode(_dbSQL), sqlite3_errmsg(_dbSQL));
        m_errors.addProblem();
        return;
    }
}
//===============================================
