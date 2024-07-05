//===============================================
#include "GSocketWin.h"
#include "GRequestHttp.h"
#include "GDispatchHttp.h"
//===============================================
#ifdef _WIN32
//===============================================
GSocketWin::GSocketWin()
: m_socket(SOCKET_ERROR) {

}
//===============================================
GSocketWin::~GSocketWin() {

}
//===============================================
void GSocketWin::run() {
    WSADATA lWSADATA;
    WORD lVersion = MAKEWORD(2, 2);
    int lError = WSAStartup(lVersion, &lWSADATA);

    if(lError != 0) {
        slog(eGERR, "L'initialisation de winsock2 a échoué."
        "|msgErreur=%s"
        "", WSAGetLastError());
        m_errors.addProblem();
        return;
    }

    m_socket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

    if(m_socket == INVALID_SOCKET) {
        slog(eGERR, "La création du socket a échoué."
        "|msgErreur=%s"
        "", WSAGetLastError());
        m_errors.addProblem();
        WSACleanup();
        return;
    }

    m_socketAddr.sin_family = AF_INET;
    m_socketAddr.sin_addr.s_addr = inet_addr("0.0.0.0");
    m_socketAddr.sin_port = htons(8080);

    if(bind(m_socket, reinterpret_cast<SOCKADDR*>(&m_socketAddr), sizeof(m_socketAddr)) == SOCKET_ERROR) {
        slog(eGERR, "La liaison du socket à l'adresse a échoué."
        "|msgErreur=%s"
        "", WSAGetLastError());
        m_errors.addProblem();
        closeServer();
        return;
    }

    if (listen(m_socket, 10) == SOCKET_ERROR) {
        slog(eGERR, "L'initialisation du nombre de connexions a échoué."
        "|msgErreur=%s"
        "", WSAGetLastError());
        m_errors.addProblem();
        closeServer();
        return;
    }

    slog(eGINF, "Démarrage du serveur...");

    sockaddr_in lAddressClient;
    int lAddressClientSize = sizeof(lAddressClient);

    while(1) {
        GSocketWin* lClient = new GSocketWin;
        int lSocketAddrSize = sizeof(lClient->m_socketAddr);

        lClient->m_socket = accept(m_socket, (struct sockaddr*)&lClient->m_socketAddr, &lSocketAddrSize);

        if (lClient->m_socket == SOCKET_ERROR) {
            slog(eGERR, "L'acceptation d'une connexion a échoué."
            "|msgErreur=%s"
            "", WSAGetLastError());
            closeServer();
            continue;
        }

        DWORD lThreadId;
        HANDLE lThreadHandle = CreateThread(
                NULL,
                0,
                onThread,
                lClient,
                0,
                &lThreadId
        );

        if(!lThreadHandle) {
            slog(eGERR, "La création du thread a échoué."
            "|msgErreur=%s"
            "", WSAGetLastError());
            continue;
        }
    }

    closeClient();
    closeServer();
}
//===============================================
GString GSocketWin::readData() {
    GString lData;
    char lBuffer[rdv::SOCKET_BUFFER_MAX];

    while(1) {
        int lBytes = recv(m_socket, lBuffer, rdv::SOCKET_BUFFER_MAX, 0);

        if(lBytes == SOCKET_ERROR) {
            slog(eGERR, "La lecture des données sur le socket a échoué."
            "|msgErreur=%s"
            "", WSAGetLastError());
            m_errors.addProblem();
            closeClient();
            break;
        }

        lBuffer[lBytes] = '\0';
        lData += lBuffer;

        u_long lBytesIO;
        if(ioctlsocket(m_socket, FIONREAD, &lBytesIO) == SOCKET_ERROR) {
            slog(eGERR, "La lecture du nombre de données restantes sur le socket a échoué."
            "|msgErreur=%s"
            "", WSAGetLastError());
            m_errors.addProblem();
            closeClient();
            break;
        }

        if(lBytesIO <= 0) break;
    }

    return lData;
}
//===============================================
void GSocketWin::sendData(const GString& _data) {
    int lBytes = send(m_socket, _data.c_str(), _data.size(), 0);

    if(lBytes == SOCKET_ERROR) {
        slog(eGERR, "La lecture des données sur le socket a échoué."
        "|msgErreur=%s"
        "", WSAGetLastError());
        m_errors.addProblem();
        closeClient();
        return;
    }
}
//===============================================
DWORD WINAPI GSocketWin::onThread(LPVOID _params) {
    GSocketWin* lClient = (GSocketWin*)_params;
    lClient->runThread();
    return 0;
}
//===============================================
void GSocketWin::runThread() {
    m_requestText = readData();

    slog(eGINF, "La réception de la requête du client est terminé."
    "|data=%s"
    "", m_requestText.c_str());

    GRequestHttp lRequestHttp;
    lRequestHttp.setRequestText(m_requestText);
    lRequestHttp.run();

    if(lRequestHttp.isHttp()) {
        GDispatchHttp lDispatchHttp;
        lDispatchHttp.setRequestHttp(lRequestHttp);
        lDispatchHttp.run();
        m_errors.addErrors(lDispatchHttp.getErrors());
        m_responseText = lDispatchHttp.getResponseText();
    }
    else {
        m_errors.addProblem();
    }

    sendResponse();
}
//===============================================
void GSocketWin::closeServer() {
    closesocket(m_socket);
    WSACleanup();
}
//===============================================
void GSocketWin::closeClient() {
    closesocket(m_socket);
    delete this;
}
//===============================================
void GSocketWin::runSuccess() {
    m_responseText = "L'opération s'est bien déroulée.";
}
//===============================================
void GSocketWin::runError() {
    m_responseText = "Un problème a été rencontré.";
}
//===============================================
void GSocketWin::sendResponse() {
    if(m_responseText.empty()) {
        if(m_errors.hasErrors()) {
            runError();
        }
        else {
            runSuccess();
        }
    }

    sendData(m_responseText);

    slog(eGINF, "L'envoi de la réponse du client est terminé."
    "|data=%s"
    "", m_responseText.c_str());

    closeClient();
}
//===============================================
#endif
//===============================================
