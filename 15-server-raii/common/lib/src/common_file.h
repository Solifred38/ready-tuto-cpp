#pragma once

#include "common_object.h"

class common_file : public common_object {
public:
    common_file(const common_string& _filename);
    ~common_file();
    bool existFile() const;
    common_string readText() ;
    common_string readBin() ;
    bool appendText(const common_string& _data);
    bool writeText(const common_string& _data);
    bool writeBin(const common_string& _data);

private:
    common_string m_filename;
};

