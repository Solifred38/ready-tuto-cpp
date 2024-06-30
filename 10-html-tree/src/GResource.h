//===============================================
#pragma once
//===============================================
#include "GObject.h"
//===============================================
class GResource : public GObject {
public:
    GResource();
    GResource(const GString& _filename);
    ~GResource();
    bool run();

public:
    void setFilename(const GString& _filename)      {m_filename = _filename;}
    const GString& getResponseType()                {return m_responseType;}
    const GString& getResponseData()                {return m_responseData;}

private:
    GString m_webRoot;
    GString m_filename;
    GString m_responseData;
    GString m_responseType;
};
//===============================================
