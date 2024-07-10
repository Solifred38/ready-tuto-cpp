//===============================================
#pragma once
//===============================================
#include "GObject.h"
//===============================================
class GRequestTotal : public GObject {
public:
    GRequestTotal(const GString& _requestText);
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
