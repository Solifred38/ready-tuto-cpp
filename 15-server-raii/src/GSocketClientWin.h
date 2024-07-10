//===============================================
#if defined(_WIN32)
//===============================================
#pragma once
//===============================================
#include "GObject.h"
//===============================================
class GSocketClientWin : public GObject {
    friend class GSocketMgrWin;

private:
    GSocketClientWin(SOCKET _socket, const GString& _addressIP, int _port, DWORD& _processId, std::vector<GSocketClientWin*>& _clientMap);

public:
    ~GSocketClientWin();
    void run();

private:
    GString readData();
    void sendData(const GString& _data);
    void runResponse();
    void runError();
    void runSuccess();

private:
    SOCKET m_socket;
    GString m_addressIP;
    int m_port;
    DWORD& m_processId;
    std::vector<GSocketClientWin*>& m_clientMap;
};
//===============================================
#endif
//===============================================
