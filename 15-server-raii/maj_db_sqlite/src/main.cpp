#include "maj_db_sqlite.h"

int main(int _argc, char** _argv) {
    std::shared_ptr<maj_db_sqlite> majSQLite = maj_db_sqlite::create(_argc, _argv);
    majSQLite->run();
    return 0;
}
