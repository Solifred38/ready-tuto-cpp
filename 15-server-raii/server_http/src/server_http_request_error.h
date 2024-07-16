#pragma once

#include "server_http_object.h"

class server_http_request_error : public server_http_object {
    friend class server_http_socket_win_client;

private:
    server_http_request_error(const common_string& _requestText);

public:
    ~server_http_request_error();
    void run();

private:
    void runHttp();

private:
    common_string m_requestText;
};
