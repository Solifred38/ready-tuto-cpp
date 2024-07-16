//===============================================
#pragma once
//===============================================
#include "GObject.h"
//===============================================
class GFile : public GObject {
public:
    GFile(const GString& _filename);
    ~GFile();
    bool existFile() const;
    GString readText() ;
    GString readBin() ;
    bool appendText(const GString& _data);
    bool writeText(const GString& _data);
    bool writeBin(const GString& _data);

private:
    GString m_filename;
};
//===============================================
