//===============================================
#pragma once
//===============================================
#include "GSocket.h"
//===============================================
#if defined(_WIN32)
//===============================================
class GSocketWin : public GSocket {
public:
    GSocketWin();
    ~GSocketWin();
    void run();
    GString readData();
    void sendData(const GString& _data);
    void closeServer();
    void closeClient();

private:
    SOCKET m_socket;
};
//===============================================
#endif
//===============================================
