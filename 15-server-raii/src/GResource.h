//===============================================
#pragma once
//===============================================
#include "GObject.h"
//===============================================
class GResource : public GObject {
public:
    GResource(const GString& _filename);
    ~GResource();
    void run();

private:
    GString m_resourceRoot;
    GString m_filename;
};
//===============================================
