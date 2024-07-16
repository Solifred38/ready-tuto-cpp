#pragma once

#include "maj_db_sqlite_header.h"

class maj_db_sqlite_script : public common_object {
    friend class maj_db_sqlite_res;

private:
    maj_db_sqlite_script(
    const common_string& _code,
    const common_string& _filename,
    const common_string& m_source);

public:
    ~maj_db_sqlite_script();
    void run();

private:
    void init();

public:
    const common_string& getCode() const        {return m_code;}
    const common_string& getFilename() const    {return m_filename;}
    const common_string& getSource() const      {return m_source;}

private:
    common_string m_code;
    common_string m_filename;
    common_string m_source;
};
