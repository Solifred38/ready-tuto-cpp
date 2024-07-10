//===============================================
#pragma once
//===============================================
#include "GObject.h"
//===============================================
class GTreeCB : public GObject {
public:
    GTreeCB(const GString& _dataJson);
    ~GTreeCB();
    void run();

private:
    GString m_dataJson;
};
//===============================================
