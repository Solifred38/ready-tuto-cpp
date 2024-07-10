//===============================================
#pragma once
//===============================================
#include "GObject.h"
//===============================================
class GRequest : public GObject {
    friend class GSocketClientWin;

private:
    GRequest(const GString& _requestText);

public:
    ~GRequest();
    void run();

private:
    GString m_requestText;
};
//===============================================
