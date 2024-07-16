#if defined(_WIN32)

#pragma once

#include "server_http_socket.h"

class server_http_socket_win : public server_http_socket {
    friend class server_http_socket;

private:
    server_http_socket_win(int _port);

public:
    ~server_http_socket_win();
    void run();
};

#endif
