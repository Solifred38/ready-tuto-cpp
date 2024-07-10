//===============================================
#pragma once
//===============================================
#include "GModule.h"
//===============================================
class GSocket : public GObject {
protected:
    GSocket(int _port);

public:
    virtual ~GSocket();
    static std::shared_ptr<GSocket> create(int _port);
    virtual void run() = 0;

protected:
    int m_port;
};
//===============================================
