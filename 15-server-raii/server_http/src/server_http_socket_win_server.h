#if defined(_WIN32)

#pragma once

#include "server_http_header.h"

class server_http_socket_win_server : public common_object {
    friend class server_http_socket_win;

private:
    server_http_socket_win_server(SOCKET _socket, int _port);

public:
    ~server_http_socket_win_server();
    void run();

private:
    static DWORD WINAPI onThread(LPVOID _params);

private:
    SOCKET m_socket;
    int m_port;
};

#endif
