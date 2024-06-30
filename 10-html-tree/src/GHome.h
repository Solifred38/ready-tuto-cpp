//===============================================
#pragma once
//===============================================
#include "GObject.h"
//===============================================
class GHome : public GObject {
public:
    GHome();
    ~GHome();
    void run();

public:
    const GString& getResponseData() const      {return m_responseData;}

private:
    GString m_templateRoot;
    GString m_responseData;
};
//===============================================
