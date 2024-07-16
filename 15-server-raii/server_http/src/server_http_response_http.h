#pragma once

#include "server_http_object.h"

class server_http_response_http : public server_http_object {
public:
    server_http_response_http(
    const common_string& _responseData
    , const common_string& _responseType
    , const e_server_http_response_http_status& _responseStatus);
    ~server_http_response_http();
    void run();
};
