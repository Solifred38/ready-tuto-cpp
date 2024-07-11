#include "db_sqlite_test.h"

int main(int _argc, char** _argv) {
    std::shared_ptr<db_sqlite_test> lProcess = db_sqlite_test::create(_argc, _argv);
    lProcess->run();
    return 0;
}
