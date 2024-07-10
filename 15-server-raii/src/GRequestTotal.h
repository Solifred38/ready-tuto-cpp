//===============================================
#pragma once
//===============================================
#include "GObject.h"
//===============================================
class GRequestTotal : public GObject {
    friend class GSocketClientWin;

private:
    GRequestTotal(const GString& _requestText);

public:
    ~GRequestTotal();
    void run();

private:
    void runHttp();

public:
    int getTotal() const        {return m_total;}

private:
    GString m_requestText;
    int m_total;
};
//===============================================
