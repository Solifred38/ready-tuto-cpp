#pragma once

#include "maj_db_sqlite.h"

class maj_db_sqlite_win : public maj_db_sqlite {
    friend class maj_db_sqlite;

private:
    maj_db_sqlite_win(int _argc, char** _argv);

public:
    ~maj_db_sqlite_win();
    void init();
};
