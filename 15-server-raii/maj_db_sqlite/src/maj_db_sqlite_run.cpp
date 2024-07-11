#include "maj_db_sqlite_run.h"

maj_db_sqlite_run::maj_db_sqlite_run(
const common_string& _code,
const common_string& _filename,
const std::vector<common_string>& _sourceList)
: m_code        (_code)
, m_filename    (_filename)
, m_sourceList  (_sourceList) {

}

maj_db_sqlite_run::~maj_db_sqlite_run() {

}

void maj_db_sqlite_run::run() {
    std::vector<common_string>::iterator it;
    for(it = m_sourceList.begin(); it != m_sourceList.end(); ++it) {
        common_string lSource = *it;
        slog(eGERR, "oooooooooooooooooooooooooooooooooooo (1)"
        "|m_code=%s"
        "|lSource=%s", m_code.c_str(), lSource.c_str());
    }
}
