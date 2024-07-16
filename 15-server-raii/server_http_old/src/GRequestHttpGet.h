//===============================================
#pragma once
//===============================================
#include "GObject.h"
//===============================================
class GRequestHttpGet : public GObject {
    friend class GRequestHttp;

private:
    GRequestHttpGet(const GString& _url, const std::map<GString, GString>& _paramsMap);

public:
    ~GRequestHttpGet();
    void run();

private:
    void runTree();
    bool loadResource();
    void runResponse();
    void runError();
    void runSuccess();

private:
    GString m_url;
    std::map<GString, GString> m_paramsMap;
};
//===============================================
