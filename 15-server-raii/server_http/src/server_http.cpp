#include "server_http.h"
#include "server_http_win.h"
#include "server_http_socket.h"

server_http::server_http(int _argc, char** _argv)
: m_argc(_argc)
, m_argv(_argv) {

}

server_http::~server_http() {

}

std::shared_ptr<server_http> server_http::create(int _argc, char** _argv) {
#if defined(_WIN32)
    return std::shared_ptr<server_http>(new server_http_win(_argc, _argv));
#endif
    return std::shared_ptr<server_http>(new server_http(_argc, _argv));
}

void server_http::run() {
    init();
    std::shared_ptr<server_http_socket> lServer = server_http_socket::create(8080);
    lServer->run();
}
