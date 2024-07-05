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

        slog(eGINF, "La détermination de l'adresse IP du client est terminée."
        "|addressIP=%s", lAddressIP.c_str());

        if (lSocket == SOCKET_ERROR) {
            slog(eGERR, "L'acceptation de la connexion du client a échoué."
            "|msgErreur=%s", WSAGetLastError());
            return;
        }

        GSocketClientWin* lClient = new GSocketClientWin(lSocket, lSizeOut, lClientMap);
        lClientMap.push_back(lClient);

        DWORD lThreadId;
        HANDLE lThreadHandle = CreateThread(
            NULL,
            0,
            onThread,
            lClient,
            0,
            &lThreadId
        );
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