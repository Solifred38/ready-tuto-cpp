//===============================================
#pragma once
//===============================================
#include "GObject.h"
//===============================================
class GRequest : public GObject {
public:
    GRequest(const GString& _requestText);
    ~GRequest();
    void run();

private:
    GString m_requestText;
};
//===============================================
