//===============================================
#pragma once
//===============================================
#include "GObject.h"
//===============================================
class GSocket {
public:
    GSocket();
    virtual ~GSocket();
    static GSocket* Create();
    virtual void run() = 0;
};
//===============================================
