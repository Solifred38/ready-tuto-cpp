//===============================================
#pragma once
//===============================================
#include "GObject.h"
//===============================================
class GModule : public GObject {
    friend class GProcess;

private:
    GModule(const GString& _module, const GString& _method, const GString& _params);

public:
    ~GModule();

public:
    void run();

private:
    void runTest();
    void runServer();

public:
    const GString& getModule()   {return m_module;}
    const GString& getMethod()   {return m_method;}
    const GString& getParams()   {return m_params;}

private:
    GString m_module;
    GString m_method;
    GString m_params;
};
//===============================================
