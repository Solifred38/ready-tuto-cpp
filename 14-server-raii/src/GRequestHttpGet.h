//===============================================
#pragma once
//===============================================
#include "GObject.h"
//===============================================
class GRequestHttpGet : public GObject {
public:
    GRequestHttpGet(const GString& _url, const std::map<GString, GString>& _paramsMap);
    ~GRequestHttpGet();
    void run();

private:
    GString m_url;
    std::map<GString, GString> m_paramsMap;
};
//===============================================
