#include "maj_db_sqlite_script.h"
#include "maj_db_sqlite_dao.h"

maj_db_sqlite_script::maj_db_sqlite_script(
const common_string& _code,
const common_string& _filename,
const common_string& _source)
: m_code        (_code)
, m_filename    (_filename)
, m_source      (_source) {
    init();
}

maj_db_sqlite_script::~maj_db_sqlite_script() {

}

void maj_db_sqlite_script::init() {
    maj_db_sqlite_dao dao;
    dao.initMaj();
    m_errors.addErrors(dao.getErrors());
}

void maj_db_sqlite_script::run() {
    maj_db_sqlite_dao dao;
    dao.runScript(m_code, m_filename, m_source);
    m_errors.addErrors(dao.getErrors());
}
