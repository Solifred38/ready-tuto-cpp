//===============================================
#pragma once
//===============================================
#include "GObject.h"
//===============================================
class GRequestHttp : public GObject {
    friend class GRequest;

private:
    GRequestHttp(const GString& _requestText);

public:
    ~GRequestHttp();
    void run();

private:
    std::map<GString, GString> getParamsMap(const GString& _paramsText) const;

private:
    GString m_requestText;
};
//===============================================
