#pragma once

#include "server_http_object.h"

class server_http_request : public server_http_object {
public:
    server_http_request(const common_string& _requestText);
    ~server_http_request();
    void run();

private:
    common_string m_requestText;
};
