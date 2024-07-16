#pragma once

#include "server_http_object.h"

class server_http_request_http : public server_http_object {
    friend class server_http_request;

private:
    server_http_request_http(const common_string& _requestText);

public:
    ~server_http_request_http();
    void run();

private:
    std::map<common_string, common_string> getParamsMap(const common_string& _paramsText) const;

private:
    common_string m_requestText;
};
