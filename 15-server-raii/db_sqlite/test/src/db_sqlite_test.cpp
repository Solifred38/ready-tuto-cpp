#include "db_sqlite_test.h"
#include "db_sqlite_test_win.h"

db_sqlite_test::db_sqlite_test(int _argc, char** _argv)
: m_argc(_argc)
, m_argv(_argv) {

}

db_sqlite_test::~db_sqlite_test() {

}

std::shared_ptr<db_sqlite_test> db_sqlite_test::create(int _argc, char** _argv) {
#if defined(_WIN32)
    return std::shared_ptr<db_sqlite_test>(new db_sqlite_test_win(_argc, _argv));
#endif
    return std::shared_ptr<db_sqlite_test>(new db_sqlite_test(_argc, _argv));
}

void db_sqlite_test::run() {
    init();
    runTest();
}

void db_sqlite_test::runTest() {
    db_sqlite dbSQL("../res", "/test.dat");
    dbSQL.insertQuery("select 'Bonjour tout le monde' as msg");
}
