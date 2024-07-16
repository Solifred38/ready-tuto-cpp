#pragma once

#include "server_http_header.h"

class server_http_socket : public common_object {
protected:
    server_http_socket(int _port);

public:
    ~server_http_socket();
    static std::shared_ptr<server_http_socket> create(int _port);
    virtual void run() {}

protected:
    int m_port;
};
