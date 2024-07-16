#pragma once

#include "server_http_header.h"

class server_http : public common_object {
protected:
    server_http(int _argc, char** _argv);

public:
    ~server_http();
    static std::shared_ptr<server_http> create(int _argc, char** _argv);
    virtual void init() {}
    void run();

private:
    int m_argc;
    char** m_argv;
};
