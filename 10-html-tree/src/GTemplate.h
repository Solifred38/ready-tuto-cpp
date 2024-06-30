//===============================================
#pragma once
//===============================================
#include "GObject.h"
//===============================================
class GTemplate : public GObject {
public:
    GTemplate();
    GTemplate(const GString& _filename);
    ~GTemplate();
    GString getData();

public:
    void setFilename(const GString& _filename)      {m_filename = _filename;}

private:
    GString m_templateRoot;
    GString m_filename;
};
//===============================================
