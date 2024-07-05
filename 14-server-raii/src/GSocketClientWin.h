//===============================================
#if defined(_WIN32)
//===============================================
#pragma once
//===============================================
#include "GObject.h"
//===============================================
class GSocketClientWin : public GObject {
public:
    GSocketClientWin(SOCKET _socket, const GString& _addressIP, std::vector<GSocketClientWin*>& _clientMap);
    ~GSocketClientWin();
    void run();
    GString readData();
    void sendData(const GString& _data);
    void closeServer();
    void closeClient();

private:
    SOCKET m_socket;
    GString m_addressIP;
    std::vector<GSocketClientWin*>& m_clientMap;
};
//===============================================
#endif
//===============================================
