//===============================================
#if defined(_WIN32)
//===============================================
#pragma once
//===============================================
#include "GObject.h"
//===============================================
class GSocketMgrWin : public GObject {
public:
    GSocketMgrWin(SOCKET _socket, int _port);
    ~GSocketMgrWin();
    void run();

private:
    static DWORD WINAPI onThread(LPVOID _params);

private:
    int m_port;
    SOCKET m_socket;
};
//===============================================
#endif
//===============================================
