#include "server_http_win.h"

server_http_win::server_http_win(int _argc, char** _argv)
: server_http(_argc, _argv) {

}

server_http_win::~server_http_win() {

}

void server_http_win::init() {
    SetConsoleOutputCP(CP_UTF8);
}
