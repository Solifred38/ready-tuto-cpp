//===============================================
#pragma once
//===============================================
#include "GObject.h"
//===============================================
class GCallback : public GObject {
public:
    GCallback();
    ~GCallback();
    void run();

public:
    const GString& getResponseData() const      {return m_responseData;}

private:
    GString m_responseData;
};
//===============================================
