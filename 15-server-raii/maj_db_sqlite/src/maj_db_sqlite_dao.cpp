#include "maj_db_sqlite_dao.h"
#include "maj_db_sqlite_run.h"
#include "db_sqlite_run.h"

maj_db_sqlite_dao::maj_db_sqlite_dao()
: m_dbRoot      ("../res")
, m_dbPath      ("/sqlite/database/test.dat") {

}

maj_db_sqlite_dao::~maj_db_sqlite_dao() {

}

void maj_db_sqlite_dao::initMaj() {
    db_sqlite dbSQL(m_dbRoot, m_dbPath);
    dbSQL.execQuery(""
    "create table if not exists _maj ( "
    "_id integer primary key autoincrement "
    ", _code varchar(6) not null "
    ", _filename varchar(255) not null "
    ", unique(_code) "
    ")");
    m_errors.addErrors(dbSQL.getErrors());
}

void maj_db_sqlite_dao::runScript(const maj_db_sqlite_run& _obj) {
    if(isRunScript(_obj)) {
        db_sqlite dbSQL(m_dbRoot, m_dbPath);
        sqlite3* dbHandler = dbSQL.open();

        if(dbHandler) {
            db_sqlite_run dbRun(dbHandler);
            dbRun.beginTransaction();

            std::vector<common_string>::const_iterator it;
            for(it = _obj.getSourceList().begin(); it != _obj.getSourceList().end(); ++it) {
                common_string lSourceSQL = *it;
                dbRun.execQuery(lSourceSQL, dbSQL.getParams());
                m_errors.addErrors(dbRun.getErrors());
                if(m_errors.hasErrors()) break;
            }

            if(!m_errors.hasErrors()) {
                dbRun.commitTransaction();
                insertScript(_obj);
            }
        }
    }
}

bool maj_db_sqlite_dao::isRunScript(const maj_db_sqlite_run& _obj) {
    db_sqlite dbSQL(m_dbRoot, m_dbPath);
    dbSQL.bindText(1, _obj.getCode());

    db_sqlite_rows lRows = dbSQL.readQuery(""
    "select count(*) from _maj m "
    "where m._code = ? "
    "");

    m_errors.addErrors(dbSQL.getErrors());
    if(m_errors.hasErrors()) return false;
    int lCount = lRows.at(0).at(0).m_dataInt;

    if(lCount > 1) {
        slog(eGERR, "Le code du script doit être unique."
        "|script=%s", _obj.getFilename().c_str());
        return false;
    }
    else if(lCount == 1) {
        slog(eGINF, "Le script a déjà été exécuté."
        "|script=%s", _obj.getFilename().c_str());
        return false;
    }

    return true;
}

int maj_db_sqlite_dao::insertScript(const maj_db_sqlite_run& _obj) {
    db_sqlite dbSQL(m_dbRoot, m_dbPath);
    dbSQL.bindText(1, _obj.getCode());
    dbSQL.bindText(2, _obj.getFilename());

    int lInsertId = dbSQL.insertQuery(""
    "insert into _maj (_code, _filename) "
    "values (?, ?) "
    "");

    m_errors.addErrors(dbSQL.getErrors());
    if(m_errors.hasErrors()) return 0;
    slog(eGINF, "Le script a été exécuté et enregistré dans la table maj."
    "|script=%s"
    "|insertId=%d", _obj.getFilename().c_str(), lInsertId);
    return lInsertId;
}
