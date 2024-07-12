#include "db_sqlite_prepare.h"

db_sqlite_prepare::db_sqlite_prepare(sqlite3_stmt* _stmtSQL)
: m_stmtSQL (_stmtSQL) {

}

db_sqlite_prepare::~db_sqlite_prepare() {
    sqlite3_finalize(m_stmtSQL);
}

void db_sqlite_prepare::execQuery(const std::vector<s_db_sqlite_param>& _params, sqlite3* _dbSQL) {
    runBind(_params, _dbSQL);
    if(m_errors.hasErrors()) return;
    int lResult = sqlite3_step(m_stmtSQL);

    if(lResult != SQLITE_DONE) {
        slog(eGERR, "L'exécution de la requête SQLITE a échoué."
        "|codeErreur=%d"
        "|msgErreur=%s", sqlite3_errcode(_dbSQL), sqlite3_errmsg(_dbSQL));
        m_errors.addProblem();
        return;
    }
}

int db_sqlite_prepare::insertQuery(const std::vector<s_db_sqlite_param>& _params, sqlite3* _dbSQL) {
    runBind(_params, _dbSQL);
    if(m_errors.hasErrors()) return 0;
    int lResult = sqlite3_step(m_stmtSQL);

    if(lResult != SQLITE_DONE) {
        slog(eGERR, "La requête d'insertion SQLITE a échoué."
        "|codeErreur=%d"
        "|msgErreur=%s", sqlite3_errcode(_dbSQL), sqlite3_errmsg(_dbSQL));
        m_errors.addProblem();
        return 0;
    }

    int lInsertId = sqlite3_last_insert_rowid(_dbSQL);
    return lInsertId;
}

db_sqlite_rows db_sqlite_prepare::readQuery(const std::vector<s_db_sqlite_param>& _params, sqlite3* _dbSQL) {
    runBind(_params, _dbSQL);
    if(m_errors.hasErrors()) return db_sqlite_rows();

    int lResult = SQLITE_DONE;
    db_sqlite_rows lRows;

    while(1) {
        lResult = sqlite3_step(m_stmtSQL);
        if(lResult != SQLITE_ROW) break;
        int lCols = sqlite3_column_count(m_stmtSQL);
        db_sqlite_row lRow;

        for(int i = 0; i < lCols; i++) {
            s_db_sqlite_col lCol;
            lCol.m_type = sqlite3_column_type(m_stmtSQL, i);
            lCol.m_name = sqlite3_column_name(m_stmtSQL, i);
            if(lCol.m_type == SQLITE_INTEGER) {
                lCol.m_dataInt = sqlite3_column_int(m_stmtSQL, i);
            }
            else if(lCol.m_type == SQLITE_FLOAT) {
                lCol.m_dataDouble = sqlite3_column_double(m_stmtSQL, i);
            }
            else if(lCol.m_type == SQLITE_TEXT) {
                char* lText = (char*)sqlite3_column_text(m_stmtSQL, i);
                int lSize = sqlite3_column_bytes(m_stmtSQL, i);
                lCol.m_dataText = common_string(lText, lSize);
            }
            else if(lCol.m_type == SQLITE_BLOB) {
                char* lBlob = (char*)sqlite3_column_blob(m_stmtSQL, i);
                int lSize = sqlite3_column_bytes(m_stmtSQL, i);
                lCol.m_dataText = common_string(lBlob, lSize);
            }

            lRow.push_back(lCol);
        }

        lRows.push_back(lRow);
    }

    if(lResult != SQLITE_DONE) {
        slog(eGERR, "La requête de sélection SQLITE a échoué."
        "|codeErreur=%d"
        "|msgErreur=%s", sqlite3_errcode(_dbSQL), sqlite3_errmsg(_dbSQL));
        m_errors.addProblem();
        return db_sqlite_rows();
    }

    return lRows;
}

void db_sqlite_prepare::runBind(const std::vector<s_db_sqlite_param>& _params, sqlite3* _dbSQL) {
    std::vector<s_db_sqlite_param>::const_iterator it;
    for(it = _params.begin(); it != _params.end(); ++it) {
        s_db_sqlite_param lParam = *it;
        if(lParam.m_type == SQLITE_NULL) {
            bindNull(lParam.m_index, _dbSQL);
            if(m_errors.hasErrors()) return;
        }
        else if(lParam.m_type == SQLITE_INTEGER) {
            bindInt(lParam.m_index, lParam.m_dataInt, _dbSQL);
            if(m_errors.hasErrors()) return;
        }
        else if(lParam.m_type == SQLITE_FLOAT) {
            bindDouble(lParam.m_index, lParam.m_dataDouble, _dbSQL);
            if(m_errors.hasErrors()) return;
        }
        else if(lParam.m_type == SQLITE_TEXT) {
            bindText(lParam.m_index, lParam.m_dataText, _dbSQL);
            if(m_errors.hasErrors()) return;
        }
        else if(lParam.m_type == SQLITE_BLOB) {
            bindBinary(lParam.m_index, lParam.m_dataText, _dbSQL);
            if(m_errors.hasErrors()) return;
        }
    }
}

void db_sqlite_prepare::bindNull(int _index, sqlite3* _dbSQL) {
    int lResult = sqlite3_bind_null(m_stmtSQL, _index);

    if(lResult != SQLITE_OK) {
        slog(eGERR, "La liaison des paramètres de la requête SQLITE a échoué."
        "|codeErreur=%d"
        "|msgErreur=%s", sqlite3_errcode(_dbSQL), sqlite3_errmsg(_dbSQL));
        m_errors.addProblem();
        return;
    }
}

void db_sqlite_prepare::bindInt(int _index, int _data, sqlite3* _dbSQL) {
    int lResult = sqlite3_bind_int(m_stmtSQL, _index, _data);

    if(lResult != SQLITE_OK) {
        slog(eGERR, "La liaison des paramètres de la requête SQLITE a échoué."
        "|codeErreur=%d"
        "|msgErreur=%s", sqlite3_errcode(_dbSQL), sqlite3_errmsg(_dbSQL));
        m_errors.addProblem();
        return;
    }
}

void db_sqlite_prepare::bindDouble(int _index, double _data, sqlite3* _dbSQL) {
    int lResult = sqlite3_bind_double(m_stmtSQL, _index, _data);

    if(lResult != SQLITE_OK) {
        slog(eGERR, "La liaison des paramètres de la requête SQLITE a échoué."
        "|codeErreur=%d"
        "|msgErreur=%s", sqlite3_errcode(_dbSQL), sqlite3_errmsg(_dbSQL));
        m_errors.addProblem();
        return;
    }
}

void db_sqlite_prepare::bindText(int _index, const common_string& _data, sqlite3* _dbSQL) {
    int lResult = sqlite3_bind_text(m_stmtSQL, _index, _data.c_str(), _data.size(), SQLITE_TRANSIENT);

    if(lResult != SQLITE_OK) {
        slog(eGERR, "La liaison des paramètres de la requête SQLITE a échoué."
        "|codeErreur=%d"
        "|msgErreur=%s", sqlite3_errcode(_dbSQL), sqlite3_errmsg(_dbSQL));
        m_errors.addProblem();
        return;
    }
}

void db_sqlite_prepare::bindBinary(int _index, const common_string& _data, sqlite3* _dbSQL) {
    int lResult = sqlite3_bind_blob(m_stmtSQL, _index, _data.c_str(), _data.size(), SQLITE_TRANSIENT);

    if(lResult != SQLITE_OK) {
        slog(eGERR, "La liaison des paramètres de la requête SQLITE a échoué."
        "|codeErreur=%d"
        "|msgErreur=%s", sqlite3_errcode(_dbSQL), sqlite3_errmsg(_dbSQL));
        m_errors.addProblem();
        return;
    }
}
