
#pragma once

#include "server_http_object.h"

class server_http_request_http_get : public server_http_object {
    friend class server_http_request_http;

private:
    server_http_request_http_get(const common_string& _url, const std::map<common_string, common_string>& _paramsMap);

public:
    ~server_http_request_http_get();
    void run();

private:
    void runTree();
    bool loadResource();
    void runResponse();
    void runError();
    void runSuccess();

private:
    common_string m_url;
    std::map<common_string, common_string> m_paramsMap;
};

