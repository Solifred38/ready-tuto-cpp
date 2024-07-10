//===============================================
#pragma once
//===============================================
#include "GObject.h"
//===============================================
class GRequestHttpPostJson : public GObject {
public:
    GRequestHttpPostJson(const GString& _url, const GString& _dataJson);
    ~GRequestHttpPostJson();
    void run();

private:
    void runTree();
    void runResponse();
    void runError();
    void runSuccess();

private:
    GString m_url;
    GString m_dataJson;
};
//===============================================
