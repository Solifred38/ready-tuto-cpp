//===============================================
#include "GSQLiteRun.h"
#include "GSQLitePrepare.h"
//===============================================
GSQLiteRun::GSQLiteRun(sqlite3* _dbSQL)
: m_dbSQL(_dbSQL) {

}
//===============================================
GSQLiteRun::~GSQLiteRun() {
    sqlite3_close(m_dbSQL);
}
//===============================================
void GSQLiteRun::execQuery(const GString& _sql) {
	int isOK = sqlite3_exec(m_dbSQL, _sql.c_str(), NULL, NULL, NULL);

    if(isOK != SQLITE_OK) {
        slog(eGERR, "L'exécution de la requête SQLITE a échoué."
        "|codeErreur=%d"
        "|msgErreur=%s"
        "|requeteSQL=%s", sqlite3_errcode(m_dbSQL), sqlite3_errmsg(m_dbSQL), _sql.c_str());
        m_errors.addProblem();
        return;
    }
}
//===============================================
void GSQLiteRun::prepareQuery(const GString& _sql, const std::vector<sGSQLiteParam>& _params) {
    sqlite3_stmt* stmtSQL;

    int isOK = sqlite3_prepare_v2(
    m_dbSQL,        /* Database handle */
    _sql.c_str(),   /* SQL statement, UTF-8 encoded */
    _sql.size(),    /* Maximum length of zSql in bytes. */
    &stmtSQL,       /* OUT: Statement handle */
    NULL            /* OUT: Pointer to unused portion of zSql */
    );

    if(isOK != SQLITE_OK) {
        slog(eGERR, "La préparation de la requête SQLITE a échoué."
        "|codeErreur=%d"
        "|msgErreur=%s"
        "|requeteSQL=%s", sqlite3_errcode(m_dbSQL), sqlite3_errmsg(m_dbSQL), _sql.c_str());
        m_errors.addProblem();
        return;
    }

    GSQLitePrepare prepareSQL(stmtSQL);
    prepareSQL.run(_params, m_dbSQL);
    m_errors.addErrors(prepareSQL.getErrors());
}
//===============================================
