//===============================================
#pragma once
//===============================================
#include "GObject.h"
//===============================================
class GRequestHttp : public GObject {
public:
    GRequestHttp(const GString& _requestText);
    ~GRequestHttp();
    void run();

private:
    std::map<GString, GString> getParamsMap(const GString& _paramsText) const;

private:
    GString m_requestText;
};
//===============================================
