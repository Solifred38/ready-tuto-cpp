#pragma once

#include "server_http.h"

class server_http_win : public server_http {
    friend class server_http;

private:
    server_http_win(int _argc, char** _argv);

public:
    ~server_http_win();
    void init();
};
