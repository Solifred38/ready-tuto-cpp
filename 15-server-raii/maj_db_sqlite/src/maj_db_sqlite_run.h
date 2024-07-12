#pragma once

#include "maj_db_sqlite_header.h"

class maj_db_sqlite_run : public common_object {
    friend class maj_db_sqlite_res;

private:
    maj_db_sqlite_run(
    const common_string& _code,
    const common_string& _filename,
    const std::vector<common_string>& _sourceList);

public:
    ~maj_db_sqlite_run();
    void run();

private:
    void init();

public:
    const common_string& getCode() const                    {return m_code;}
    const common_string& getFilename() const                {return m_filename;}
    const std::vector<common_string>& getSourceList() const     {return m_sourceList;}

private:
    common_string m_code;
    common_string m_filename;
    std::vector<common_string> m_sourceList;
};
