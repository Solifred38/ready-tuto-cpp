#if defined(_WIN32)

#include "server_http_socket_win_server.h"
#include "server_http_socket_win_client.h"

server_http_socket_win_server::server_http_socket_win_server(SOCKET _socket, int _port)
: m_socket  (_socket)
, m_port    (_port) {

}

server_http_socket_win_server::~server_http_socket_win_server() {
    closesocket(m_socket);
}


void server_http_socket_win_server::run() {
    BOOL lReuseAddr = TRUE;
    int lReuseLen = sizeof(BOOL);
    int isReuseAddr = setsockopt(m_socket, SOL_SOCKET, SO_REUSEADDR, (char*)&lReuseAddr, lReuseLen);

    if(isReuseAddr == SOCKET_ERROR) {
        slog(eGERR, "L'initialisation de l'option SO_REUSEADDR sur le socket a échoué."
        "|msgErreur=%s", WSAGetLastError());
        m_errors.addProblem();
        return;
    }

    sockaddr_in lAddressIn;
    lAddressIn.sin_family = AF_INET;
    lAddressIn.sin_addr.s_addr = inet_addr("0.0.0.0");
    lAddressIn.sin_port = htons(m_port);

    if(bind(m_socket, reinterpret_cast<SOCKADDR*>(&lAddressIn), sizeof(lAddressIn)) == SOCKET_ERROR) {
        slog(eGERR, "La liaison du socket à l'adresse a échoué."
        "|msgErreur=%s", WSAGetLastError());
        return;
    }

    if (listen(m_socket, 10) == SOCKET_ERROR) {
        slog(eGERR, "L'initialisation du nombre de connexions a échoué."
        "|msgErreur=%s", WSAGetLastError());
        return;
    }

    slog(eGINF, "Démarrage du serveur...");

    std::vector<server_http_socket_win_client*> lClientMap;

    while(1) {
        sockaddr_in lAddressOut;
        int lSizeOut        = sizeof(lAddressOut);

        SOCKET lSocket      = accept(m_socket, (struct sockaddr*)&lAddressOut, &lSizeOut);

        common_string lAddressIP  = inet_ntoa(lAddressOut.sin_addr);
        int lPort           = ntohs(lAddressOut.sin_port);

        slog(eGINF, "La détermination de l'adresse IP du client est terminée."
        "|addressIP=%s"
        "|port=%d", lAddressIP.c_str(), lPort);

        if (lSocket == SOCKET_ERROR) {
            slog(eGERR, "L'acceptation de la connexion du client a échoué."
            "|msgErreur=%s", WSAGetLastError());
            continue;
        }

        DWORD lThreadId;

        server_http_socket_win_client* lClient = new server_http_socket_win_client(lSocket, lAddressIP, lPort, lThreadId, lClientMap);
        lClientMap.push_back(lClient);

        HANDLE lThreadHandle = CreateThread(
            NULL,
            0,
            onThread,
            lClient,
            0,
            &lThreadId
        );

        if (!lThreadHandle) {
            slog(eGERR, "La création du thread a échoué."
            "|msgErreur=%s", GetLastError());
            continue;
        }
    }
}

DWORD WINAPI server_http_socket_win_server::onThread(LPVOID _params) {
    std::shared_ptr<server_http_socket_win_client> lClient((server_http_socket_win_client*)_params);
    lClient->run();
    return 0;
}

#endif
