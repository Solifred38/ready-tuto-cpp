#include "maj_db_sqlite_win.h"

maj_db_sqlite_win::maj_db_sqlite_win(int _argc, char** _argv)
: maj_db_sqlite(_argc, _argv) {

}

maj_db_sqlite_win::~maj_db_sqlite_win() {

}

void maj_db_sqlite_win::init() {
    SetConsoleOutputCP(CP_UTF8);
}
