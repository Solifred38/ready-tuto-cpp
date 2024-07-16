#include "server_http_socket.h"
#include "server_http_socket_win.h"

server_http_socket::server_http_socket(int _port)
: m_port(_port) {

}

server_http_socket::~server_http_socket() {

}

std::shared_ptr<server_http_socket> server_http_socket::create(int _port) {
#if defined(_WIN32)
    return std::shared_ptr<server_http_socket>(new server_http_socket_win(_port));
#endif
    return std::shared_ptr<server_http_socket>(new server_http_socket(_port));
}
