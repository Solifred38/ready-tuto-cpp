//===============================================
#pragma once
//===============================================
#include "GModule.h"
//===============================================
class GTest : public GObject {
public:
    GTest(const GModule& _module);
    ~GTest();
    void run();

private:
    void runTest();

private:
    GModule m_module;
};
//===============================================
