//===============================================
#pragma once
//===============================================
#include "GRequestHttp.h"
//===============================================
class GDispatchHttp : public GObject {
public:
    GDispatchHttp();
    ~GDispatchHttp();
    void run();

private:
    void runResponse();
    bool loadResource();
    void runError();
    void runSuccess();
    void runHome();
    void runCallback();

public:
    void setRequestHttp(const GRequestHttp& _requestHttp)       {m_requestHttp = _requestHttp;}
    const GString& getResponseText() const                      {return m_responseText;}

private:
    GRequestHttp m_requestHttp;
    GString m_responseType;
    GString m_responseData;
    GString m_responseText;
};
//===============================================
