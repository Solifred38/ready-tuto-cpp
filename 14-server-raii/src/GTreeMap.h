//===============================================
#pragma once
//===============================================
#include "GObject.h"
//===============================================
class GTreeMap : public GObject {
public:
    GTreeMap(const GString& _dataJson);
    ~GTreeMap();
    void run();

private:
    GString m_dataJson;
};
//===============================================
