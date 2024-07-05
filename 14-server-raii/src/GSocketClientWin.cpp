//===============================================
#if defined(_WIN32)
//===============================================
#include "GSocketClientWin.h"
#include "GRequest.h"
#include "GResponseHttp.h"
//===============================================
GSocketClientWin::GSocketClientWin(SOCKET _socket, const GString& _addressIP, std::vector<GSocketClientWin*>& _clientMap)
: m_socket      (_socket)
, m_addressIP   (_addressIP)
, m_clientMap   (_clientMap) {

}
//===============================================
GSocketClientWin::~GSocketClientWin() {
    closesocket(m_socket);
    std::vector<GSocketClientWin*>::iterator it;
    it = std::find(m_clientMap.begin(), m_clientMap.end(), this);
    if(it != m_clientMap.end()) {
        m_clientMap.erase(it);
    }
}
//===============================================
void GSocketClientWin::run() {
    GString lRequestText = readData();

    slog(eGINF, "La réception de la requête du client."
    "|requestText=%s", lRequestText.c_str());

    GRequest lRequest(lRequestText);
    lRequest.run();

    std::string lResponseData = "<h1>Bonjour tout le monde.</h1>";
    GResponseHttp lResponseHttp(lResponseData);
    GString lResponseText = lResponseHttp.getResponseText();
    sendData(lResponseText);

    slog(eGINF, "L'envoi de la requête du client est terminé."
    "|data=%s", lResponseText.c_str());
}
//===============================================
GString GSocketClientWin::readData() {
    GString lData;
    char lBuffer[rdv::SOCKET_BUFFER_MAX];

    while(1) {
        int lBytes = recv(m_socket, lBuffer, rdv::SOCKET_BUFFER_MAX, 0);

        if(lBytes == SOCKET_ERROR) {
            fprintf(stdout, "La lecture des données sur le socket a échoué."
            "|msgErreur=%s", WSAGetLastError());
            closeClient();
            break;
        }

        lBuffer[lBytes] = '\0';
        lData += lBuffer;

        u_long lBytesIO;
        if(ioctlsocket(m_socket, FIONREAD, &lBytesIO) == SOCKET_ERROR) {
            fprintf(stdout, "La lecture du nombre de données restantes sur le socket a échoué."
            "|msgErreur=%s", WSAGetLastError());
            closeClient();
            break;
        }

        if(lBytesIO <= 0) break;
    }

    return lData;
}
//===============================================
void GSocketClientWin::sendData(const GString& _data) {
    int lBytes = send(m_socket, _data.c_str(), _data.size(), 0);

    if(lBytes == SOCKET_ERROR) {
        fprintf(stdout, "La lecture des données sur le socket a échoué."
        "|msgErreur=%s", WSAGetLastError());
        closeClient();
        return;
    }
}
//===============================================
void GSocketClientWin::closeServer() {
    closesocket(m_socket);
    WSACleanup();
}
//===============================================
void GSocketClientWin::closeClient() {
    closesocket(m_socket);
}
//===============================================
#endif
//===============================================
