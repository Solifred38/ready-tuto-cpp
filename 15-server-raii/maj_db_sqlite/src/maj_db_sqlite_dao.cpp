#include "maj_db_sqlite_dao.h"
#include "maj_db_sqlite_run.h"
#include "maj_db_sqlite_script.h"
#include "db_sqlite_run.h"

maj_db_sqlite_dao::maj_db_sqlite_dao()
: m_dbRoot      ("../res")
, m_dbPath      ("/private/database/sqlite/db/test/test.dat") {

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
    if(isRunScript(_obj.getCode(), _obj.getFilename())) {
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
                insertScript(_obj.getCode(), _obj.getFilename());
            }
        }
    }
}

void maj_db_sqlite_dao::runScript(const common_string& _code, const common_string& _filename, const common_string& _source) {
    if(isRunScript(_code, _filename)) {
        db_sqlite dbSQL(m_dbRoot, m_dbPath);
        sqlite3* dbHandler = dbSQL.open();

        if(dbHandler) {
            db_sqlite_run dbRun(dbHandler);
            dbRun.beginTransaction();

            dbRun.execQuery(_source, dbSQL.getParams());
            m_errors.addErrors(dbRun.getErrors());
            if(m_errors.hasErrors()) return;

            if(!m_errors.hasErrors()) {
                dbRun.commitTransaction();
                insertScript(_code, _filename);
            }
        }
    }
}

bool maj_db_sqlite_dao::isRunScript(const common_string& _code, const common_string& _filename) {
    db_sqlite dbSQL(m_dbRoot, m_dbPath);
    dbSQL.bindText(1, _code);

    db_sqlite_rows lRows = dbSQL.readQuery(""
    "select count(*) from _maj m "
    "where m._code = ? "
    "");

    m_errors.addErrors(dbSQL.getErrors());
    if(m_errors.hasErrors()) return false;
    int lCount = lRows.at(0).at(0).m_dataInt;

    if(lCount > 1) {
        slog(eGERR, "Le code du script doit être unique."
        "|script=%s", _filename.c_str());
        return false;
    }
    else if(lCount == 1) {
        slog(eGINF, "Le script a déjà été exécuté."
        "|script=%s", _filename.c_str());
        return false;
    }

    return true;
}

int maj_db_sqlite_dao::insertScript(const common_string& _code, const common_string& _filename) {
    db_sqlite dbSQL(m_dbRoot, m_dbPath);
    dbSQL.bindText(1, _code);
    dbSQL.bindText(2, _filename);

    int lInsertId = dbSQL.insertQuery(""
    "insert into _maj (_code, _filename) "
    "values (?, ?) "
    "");

    m_errors.addErrors(dbSQL.getErrors());
    if(m_errors.hasErrors()) return 0;
    slog(eGINF, "Le script a été exécuté et enregistré."
    "|script=%s"
    "|insertId=%d", _filename.c_str(), lInsertId);
    return lInsertId;
}
