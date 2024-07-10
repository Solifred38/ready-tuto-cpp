//===============================================
#if defined(_WIN32)
//===============================================
#include "GSocketWin.h"
#include "GSocketMgrWin.h"
//===============================================
GSocketWin::GSocketWin(int _port)
: GSocket(_port) {

}
//===============================================
GSocketWin::~GSocketWin() {
    WSACleanup();
}
//===============================================
void GSocketWin::run() {
    WSADATA lWSADATA;
    WORD lVersion = MAKEWORD(2, 2);
    int lError = WSAStartup(lVersion, &lWSADATA);

    if(lError != 0) {
        slog(eGERR, "Erreur lors de l'initialisation de winsock2."
        "|msgErreur=%s", WSAGetLastError());
        return;
    }

    int lSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

    if(lSocket == INVALID_SOCKET) {
        slog(eGERR, "Erreur lors de la création du socket."
        "|msgErreur=%s", WSAGetLastError());
        return;
    }

    GSocketMgrWin lServer(lSocket, m_port);
    lServer.run();
}
//===============================================
#endif
//===============================================
