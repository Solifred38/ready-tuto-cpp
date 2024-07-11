//===============================================
#if defined(_WIN32)
//===============================================
#include "GSocketClientWin.h"
#include "GRequest.h"
#include "GRequestTotal.h"
#include "GRequestError.h"
#include "GResponseHttp.h"
//===============================================
GSocketClientWin::GSocketClientWin(SOCKET _socket, const GString& _addressIP, int _port, DWORD& _processId, std::vector<GSocketClientWin*>& _clientMap)
: m_socket      (_socket)
, m_addressIP   (_addressIP)
, m_port        (_port)
, m_processId   (_processId)
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

    if(!m_errors.hasErrors()) {
        GRequest lRequest(lRequestText);
        lRequest.run();
        m_errors.addErrors(lRequest.getErrors());
        m_responseText = lRequest.getResponseText();
    }
    else {
        GRequestError lError(lRequestText);
        lError.run();
        m_responseText = lError.getResponseText();
    }
    runResponse();
}
//===============================================
GString GSocketClientWin::readData() {
    GString lData;
    char lBuffer[rdv::SOCKET_BUFFER_MAX];
    bool isData = false;
    int lTotal = 0;

    while(1) {
        int lBytes = recv(m_socket, lBuffer, rdv::SOCKET_BUFFER_MAX, 0);

        if(lBytes == SOCKET_ERROR) {
            slog(eGERR, "La lecture des données sur le socket a échoué."
            "|msgErreur=%s"
            "|requete=%s", WSAGetLastError(), lData.limit(100).c_str());
            m_errors.addProblem();
            break;
        }

        lBuffer[lBytes] = '\0';
        lData += lBuffer;

        if(lData.size() > rdv::SOCKET_BUFFER_MAX) {
            slog(eGERR, "La taille maximale de la requête est atteinte."
            "|size=%d"
            "|max=%d"
            "|requête=%s", lData.size(), rdv::SOCKET_BUFFER_MAX, lData.limit(100).c_str());
            m_errors.addProblem();
            break;
        }

        if(!isData) {
            GRequestTotal lRequestTotal(lData);
            lRequestTotal.run();
            lTotal = lRequestTotal.getTotal();
            isData = true;
        }

        u_long lBytesIO;
        if(ioctlsocket(m_socket, FIONREAD, &lBytesIO) == SOCKET_ERROR) {
            slog(eGERR, "La lecture du nombre de données restantes sur le socket a échoué."
            "|msgErreur=%s"
            "|requete=%s", WSAGetLastError(), lData.limit(100).c_str());
            m_errors.addProblem();
            break;
        }

        if((lBytesIO == 0) && (lData.size() >= lTotal)) break;
    }

    slog(eGINF, "La réception de la requête du client est terminée."
    "|data=%s", lData.limit(100).c_str());

    return lData;
}
//===============================================
void GSocketClientWin::sendData(const GString& _data) {
    slog(eGINF, "L'envoi de la requête du client est terminé."
    "|data=%s", _data.limit(100).c_str());

    int lBytes = send(m_socket, _data.c_str(), _data.size(), 0);

    if(lBytes == SOCKET_ERROR) {
        slog(eGERR, "La lecture des données sur le socket a échoué."
        "|msgErreur=%s", WSAGetLastError());
        m_errors.addProblem();
        return;
    }
}
//===============================================
void GSocketClientWin::runResponse() {
    if(m_responseText.empty()) {
        if(m_errors.hasErrors()) {
            runError();
        }
        else {
            runSuccess();
        }
    }

    sendData(m_responseText);
}
//===============================================
void GSocketClientWin::runError() {
    m_responseText = "Un problème a été rencontré.";
}
//===============================================
void GSocketClientWin::runSuccess() {
    m_responseText = "L'opération s'est déroulée avec success.";
}
//===============================================
#endif
//===============================================
