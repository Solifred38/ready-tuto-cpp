
#if defined(_WIN32)

#pragma once

#include "server_http_object.h"

class server_http_socket_win_client : public server_http_object {
    friend class server_http_socket_win_server;

private:
    server_http_socket_win_client(SOCKET _socket, const common_string& _addressIP, int _port, DWORD& _processId, std::vector<server_http_socket_win_client*>& _clientMap);

public:
    ~server_http_socket_win_client();
    void run();

private:
    common_string readData();
    void sendData(const common_string& _data);
    void runResponse();
    void runError();
    void runSuccess();

private:
    SOCKET m_socket;
    common_string m_addressIP;
    int m_port;
    DWORD& m_processId;
    std::vector<server_http_socket_win_client*>& m_clientMap;
};

#endif

