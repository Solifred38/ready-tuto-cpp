//===============================================
#pragma once
//===============================================
#include "GObject.h"
//===============================================
class GRequestError : public GObject {
public:
    GRequestError(const GString& _requestText);
    ~GRequestError();
    void run();

private:
    void runHttp();

private:
    GString m_requestText;
};
//===============================================
