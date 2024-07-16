#pragma once

#include "server_http_object.h"

class server_http_request_http_post_json : public server_http_object {
    friend class server_http_request_http;

private:
    server_http_request_http_post_json(const common_string& _url, const common_string& _dataJson);

public:
    ~server_http_request_http_post_json();
    void run();

private:
    void runTree();
    void runResponse();
    void runError();
    void runSuccess();

private:
    common_string m_url;
    common_string m_dataJson;
};

