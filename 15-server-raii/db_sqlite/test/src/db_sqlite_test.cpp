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
    {
        db_sqlite dbSQL("../res", "/test.dat");

        dbSQL.execQuery(""
        "drop table _test "
        "");
    }
    {
        db_sqlite dbSQL("../res", "/test.dat");

        dbSQL.execQuery(""
        "create table _test ( "
        "_id integer primary key autoincrement "
        ", _code int not null "
        ", _name text not null "
        ")"
        "");
    }
    {
        db_sqlite dbSQL("../res", "/test.dat");

        for(int i = 0; i < 5; i++) {
            dbSQL.bindInt(1, 1234 + i*1000);
            dbSQL.bindText(2, "Gerard KESSE");

            int lId = dbSQL.insertQuery(""
            "insert into _test (_code, _name) "
            "values (?, ?) "
            "");

            if(!dbSQL.getErrors().hasErrors()) {
                slog(eGINF, "L'insertion de la donnée est terminée."
                "|id=%d", lId);
            }
            else {
                m_errors.addErrors(dbSQL.getErrors());
                break;
            }
        }
    }
    {
        db_sqlite dbSQL("../res", "/test.dat");
        sqlite3* dbHandler = dbSQL.open();
        if(dbHandler) {
            db_sqlite_run dbRun(dbHandler);
            dbRun.beginTransaction();

            for(int i = 5; i < 10; i++) {
                dbSQL.bindInt(1, 1234 + i*1000);
                dbSQL.bindText(2, "Deborah YOBOUE");

                int lId = dbRun.insertQuery(""
                "insert into _test (_code, _name) "
                "values (?, ?) "
                "", dbSQL.getParams());

                if(!dbSQL.getErrors().hasErrors()) {
                    slog(eGINF, "L'insertion de la donnée est terminée."
                    "|id=%d", lId);
                }
                else {
                    m_errors.addErrors(dbSQL.getErrors());
                    break;
                }
            }

            if(!m_errors.hasErrors()) {
                //dbRun.commitTransaction();
            }
        }
    }
    {
        db_sqlite dbSQL("../res", "/test.dat");

        for(int i = 0; i < 3; i++) {
            dbSQL.bindInt(1, 1234 + i*1000);
            dbSQL.bindText(2, "Bryan KESSE");

            int lId = dbSQL.insertQuery(""
            "insert into _test (_code, _name) "
            "values (?, ?) "
            "");

            if(!dbSQL.getErrors().hasErrors()) {
                slog(eGINF, "L'insertion de la donnée est terminée."
                "|id=%d", lId);
            }
            else {
                m_errors.addErrors(dbSQL.getErrors());
                break;
            }
        }
    }
    {
        db_sqlite dbSQL("../res", "/test.dat");
        db_sqlite_rows lRows = dbSQL.readQuery(""
        "select _id, _code, _name "
        "from _test "
        "");

        for(int i = 0; i < lRows.size(); i++) {
            std::cout << lRows.at(i).at(0).m_name << " | ";
            std::cout << lRows.at(i).at(0).m_dataInt << " | ";
            std::cout << lRows.at(i).at(1).m_name << " | ";
            std::cout << lRows.at(i).at(1).m_dataInt << " | ";
            std::cout << lRows.at(i).at(2).m_name << " | ";
            std::cout << lRows.at(i).at(2).m_dataText << std::endl;
        }

    }
}
