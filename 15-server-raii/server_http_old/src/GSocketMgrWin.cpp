//===============================================
#if defined(_WIN32)
//===============================================
#include "GSocketMgrWin.h"
#include "GSocketClientWin.h"
//===============================================
GSocketMgrWin::GSocketMgrWin(SOCKET _socket, int _port)
: m_socket  (_socket)
, m_port    (_port) {

}
//===============================================
GSocketMgrWin::~GSocketMgrWin() {
    closesocket(m_socket);
}
//===============================================
void GSocketMgrWin::run() {
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

    std::vector<GSocketClientWin*> lClientMap;

    while(1) {
        sockaddr_in lAddressOut;
        int lSizeOut        = sizeof(lAddressOut);

        SOCKET lSocket      = accept(m_socket, (struct sockaddr*)&lAddressOut, &lSizeOut);

        GString lAddressIP  = inet_ntoa(lAddressOut.sin_addr);
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

        GSocketClientWin* lClient = new GSocketClientWin(lSocket, lAddressIP, lPort, lThreadId, lClientMap);
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
//===============================================
DWORD WINAPI GSocketMgrWin::onThread(LPVOID _params) {
    std::shared_ptr<GSocketClientWin> lClient((GSocketClientWin*)_params);
    lClient->run();
    return 0;
}
//===============================================
#endif
//===============================================