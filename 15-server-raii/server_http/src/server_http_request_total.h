
#pragma once

#include "server_http_header.h"

class server_http_request_total : public common_object {
    friend class server_http_socket_win_client;

private:
    server_http_request_total(const common_string& _requestText);

public:
    ~server_http_request_total();
    void run();

private:
    void runHttp();

public:
    int getTotal() const        {return m_total;}

private:
    common_string m_requestText;
    int m_total;
};

