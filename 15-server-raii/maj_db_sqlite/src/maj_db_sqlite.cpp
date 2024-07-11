#include "maj_db_sqlite.h"
#include "maj_db_sqlite_win.h"
#include "maj_db_sqlite_res.h"

maj_db_sqlite::maj_db_sqlite(int _argc, char** _argv)
: m_argc(_argc)
, m_argv(_argv) {

}

maj_db_sqlite::~maj_db_sqlite() {

}

std::shared_ptr<maj_db_sqlite> maj_db_sqlite::create(int _argc, char** _argv) {
#if defined(_WIN32)
    return std::shared_ptr<maj_db_sqlite>(new maj_db_sqlite_win(_argc, _argv));
#endif
    return std::shared_ptr<maj_db_sqlite>(new maj_db_sqlite(_argc, _argv));
}

void maj_db_sqlite::run() {
    init();
    maj_db_sqlite_res resource;
    resource.run();
}
