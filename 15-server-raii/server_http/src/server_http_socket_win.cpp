#if defined(_WIN32)

#include "server_http_socket_win.h"
#include "server_http_socket_win_server.h"

server_http_socket_win::server_http_socket_win(int _port)
: server_http_socket(_port) {

}

server_http_socket_win::~server_http_socket_win() {
    WSACleanup();
}

void server_http_socket_win::run() {
    WSADATA lWSADATA;
    WORD lVersion = MAKEWORD(2, 2);
    int lError = WSAStartup(lVersion, &lWSADATA);

    if(lError != 0) {
        slog(eGERR, "Erreur lors de l'initialisation de winsock2."
        "|msgErreur=%s", WSAGetLastError());
        m_errors.addProblem();
        return;
    }

    int lSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

    if(lSocket == INVALID_SOCKET) {
        slog(eGERR, "Erreur lors de la création du socket."
        "|msgErreur=%s", WSAGetLastError());
        m_errors.addProblem();
        return;
    }

    server_http_socket_win_server lServer(lSocket, m_port);
    lServer.run();
}

#endif
