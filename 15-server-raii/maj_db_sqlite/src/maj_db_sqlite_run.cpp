#include "maj_db_sqlite_run.h"
#include "maj_db_sqlite_dao.h"

maj_db_sqlite_run::maj_db_sqlite_run(
const common_string& _code,
const common_string& _filename,
const std::vector<common_string>& _sourceList)
: m_code        (_code)
, m_filename    (_filename)
, m_sourceList  (_sourceList) {
    init();
}

maj_db_sqlite_run::~maj_db_sqlite_run() {

}

void maj_db_sqlite_run::init() {
    maj_db_sqlite_dao dao;
    dao.initMaj();
    m_errors.addErrors(dao.getErrors());
}

void maj_db_sqlite_run::run() {
    maj_db_sqlite_dao dao;
    dao.runScript(*this);
    m_errors.addErrors(dao.getErrors());
}
