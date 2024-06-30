//===============================================
#pragma once
//===============================================
#include "GObject.h"
//===============================================
class GSocket : public GObject {
public:
    GSocket();
    virtual ~GSocket();
    static GSocket* Create();
    virtual void run() = 0;
};
//===============================================
