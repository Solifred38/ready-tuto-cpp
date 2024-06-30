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

private:
    GString readData();
    void sendData(const GString& _data);
    void closeServer();
    void closeClient();
    static DWORD WINAPI onThread(LPVOID _params);
    void runThread();
    void runSuccess();
    void runError();
    void sendResponse();

private:
    SOCKET m_socket;
    sockaddr_in m_socketAddr;
    GString m_requestText;
    GString m_responseText;
};
//===============================================
#endif
//===============================================
