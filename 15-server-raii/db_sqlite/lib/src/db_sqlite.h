#pragma once

#include "db_sqlite_header.h"

struct s_db_sqlite_param {
    int m_type;
    int m_index;
    int m_dataInt;
    double m_dataDouble;
    common_string m_dataText;
};

struct s_db_sqlite_col {
    int m_type;
    common_string m_name;
    int m_dataInt;
    double m_dataDouble;
    common_string m_dataText;
};

typedef std::vector<s_db_sqlite_col> db_sqlite_row;
typedef std::vector<db_sqlite_row> db_sqlite_rows;

class db_sqlite : public common_object {
public:
    db_sqlite();
    db_sqlite(const common_string& _dbPath);
    db_sqlite(const common_string& _dbRoot, const common_string& _dbPath);
    ~db_sqlite();
    void execQuery(const common_string& _sql);
    int insertQuery(const common_string& _sql);
    db_sqlite_rows readQuery(const common_string& _sql);
    void bindNull(int _index);
    void bindInt(int _index, int _data);
    void bindDouble(int _index, double _data);
    void bindText(int _index, const common_string& _data);
    void bindBinary(int _index, const common_string& _data);

private:
    common_string m_dbRoot;
    common_string m_dbPath;
    std::vector<s_db_sqlite_param> m_params;
};

