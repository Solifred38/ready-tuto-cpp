
#include "db_sqlite_run.h"
#include "db_sqlite_prepare.h"

db_sqlite_run::db_sqlite_run(sqlite3* _dbSQL)
: m_dbSQL(_dbSQL) {

}

db_sqlite_run::~db_sqlite_run() {
    sqlite3_close(m_dbSQL);
}

void db_sqlite_run::execQuery(const common_string& _sql, const std::vector<s_db_sqlite_param>& _params) {
    sqlite3_stmt* stmtSQL;
    const char* nextSQL;
    common_string curSQL = _sql;

    while(1) {
        int lResult = sqlite3_prepare_v2(
        m_dbSQL,        /* Database handle */
        curSQL.c_str(),   /* SQL statement, UTF-8 encoded */
        curSQL.size(),    /* Maximum length of zSql in bytes. */
        &stmtSQL,       /* OUT: Statement handle */
        &nextSQL        /* OUT: Pointer to unused portion of zSql */
        );

        if(lResult != SQLITE_OK) {
            slog(eGERR, "La préparation de la requête SQLITE a échoué."
            "|codeErreur=%d"
            "|msgErreur=%s"
            "|requeteSQL=%s", sqlite3_errcode(m_dbSQL), sqlite3_errmsg(m_dbSQL), _sql.c_str());
            m_errors.addProblem();
            return;
        }

        db_sqlite_prepare prepareSQL(stmtSQL);
        prepareSQL.execQuery(_params, m_dbSQL);
        m_errors.addErrors(prepareSQL.getErrors());
        if(m_errors.hasErrors()) break;
        curSQL = nextSQL;
        if(curSQL.trim().empty()) break;
    }
}

int db_sqlite_run::insertQuery(const common_string& _sql, const std::vector<s_db_sqlite_param>& _params) {
    sqlite3_stmt* stmtSQL;
    int lInsertId = 0;

    int lResult = sqlite3_prepare_v2(
    m_dbSQL,        /* Database handle */
    _sql.c_str(),   /* SQL statement, UTF-8 encoded */
    _sql.size(),    /* Maximum length of zSql in bytes. */
    &stmtSQL,       /* OUT: Statement handle */
    NULL            /* OUT: Pointer to unused portion of zSql */
    );

    if(lResult != SQLITE_OK) {
        slog(eGERR, "La préparation de la requête SQLITE a échoué."
        "|codeErreur=%d"
        "|msgErreur=%s"
        "|requeteSQL=%s", sqlite3_errcode(m_dbSQL), sqlite3_errmsg(m_dbSQL), _sql.c_str());
        m_errors.addProblem();
        return lInsertId;
    }

    db_sqlite_prepare prepareSQL(stmtSQL);
    lInsertId = prepareSQL.insertQuery(_params, m_dbSQL);
    m_errors.addErrors(prepareSQL.getErrors());
    return lInsertId;
}

db_sqlite_rows db_sqlite_run::readQuery(const common_string& _sql, const std::vector<s_db_sqlite_param>& _params) {
    sqlite3_stmt* stmtSQL;
    db_sqlite_rows lRows;

    int lResult = sqlite3_prepare_v2(
    m_dbSQL,        /* Database handle */
    _sql.c_str(),   /* SQL statement, UTF-8 encoded */
    _sql.size(),    /* Maximum length of zSql in bytes. */
    &stmtSQL,       /* OUT: Statement handle */
    NULL            /* OUT: Pointer to unused portion of zSql */
    );

    if(lResult != SQLITE_OK) {
        slog(eGERR, "La préparation de la requête SQLITE a échoué."
        "|codeErreur=%d"
        "|msgErreur=%s"
        "|requeteSQL=%s", sqlite3_errcode(m_dbSQL), sqlite3_errmsg(m_dbSQL), _sql.c_str());
        m_errors.addProblem();
        return lRows;
    }

    db_sqlite_prepare prepareSQL(stmtSQL);
    lRows = prepareSQL.readQuery(_params, m_dbSQL);
    m_errors.addErrors(prepareSQL.getErrors());
    return lRows;
}

void db_sqlite_run::beginTransaction() {
    sqlite3_exec(m_dbSQL, "BEGIN TRANSACTION;", NULL, NULL, NULL);
}

void db_sqlite_run::commitTransaction() {
    sqlite3_exec(m_dbSQL, "END TRANSACTION;", NULL, NULL, NULL);
}
