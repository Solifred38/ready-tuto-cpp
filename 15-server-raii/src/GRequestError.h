//===============================================
#pragma once
//===============================================
#include "GObject.h"
//===============================================
class GRequestError : public GObject {
    friend class GSocketClientWin;

private:
    GRequestError(const GString& _requestText);

public:
    ~GRequestError();
    void run();

private:
    void runHttp();

private:
    GString m_requestText;
};
//===============================================
