//===============================================
#pragma once
//===============================================
#include "GRequestHttp.h"
//===============================================
class GDispatchHttp {
public:
    GDispatchHttp();
    ~GDispatchHttp();
    void run();

private:
    void runResponse();
    void runError();
    void runSuccess();
    void runHome();
    void runCallback();

public:
    void setRequestHttp(const GRequestHttp& _requestHttp)       {m_requestHttp = _requestHttp;}
    const GString& getResponseText() const                      {return m_responseText;}
    const GError& getErrors() const                             {return m_errors;}

private:
    GRequestHttp m_requestHttp;
    GString m_responseData;
    GString m_responseText;
    GError m_errors;
    GLog slog;
};
//===============================================
