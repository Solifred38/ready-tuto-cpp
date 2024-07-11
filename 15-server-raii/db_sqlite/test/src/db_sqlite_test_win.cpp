#include "db_sqlite_test_win.h"

db_sqlite_test_win::db_sqlite_test_win(int _argc, char** _argv)
: db_sqlite_test(_argc, _argv) {

}

db_sqlite_test_win::~db_sqlite_test_win() {

}

void db_sqlite_test_win::init() {
    SetConsoleOutputCP(CP_UTF8);
}
