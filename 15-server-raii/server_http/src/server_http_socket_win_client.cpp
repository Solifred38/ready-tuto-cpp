
#if defined(_WIN32)

#include "server_http_socket_win_client.h"
#include "server_http_request.h"
#include "server_http_request_total.h"
#include "server_http_request_error.h"

server_http_socket_win_client::server_http_socket_win_client(SOCKET _socket, const common_string& _addressIP, int _port, DWORD& _processId, std::vector<server_http_socket_win_client*>& _clientMap)
: m_socket      (_socket)
, m_addressIP   (_addressIP)
, m_port        (_port)
, m_processId   (_processId)
, m_clientMap   (_clientMap) {

}

server_http_socket_win_client::~server_http_socket_win_client() {
    closesocket(m_socket);
    std::vector<server_http_socket_win_client*>::iterator it;
    it = std::find(m_clientMap.begin(), m_clientMap.end(), this);
    if(it != m_clientMap.end()) {
        m_clientMap.erase(it);
    }
}

void server_http_socket_win_client::run() {
    common_string lRequestText = readData();

    if(!m_errors.hasErrors()) {
        server_http_request lRequest(lRequestText);
        lRequest.run();
        m_errors.addErrors(lRequest.getErrors());
        m_responseText = lRequest.getResponseText();
    }
    else {
        server_http_request_error lError(lRequestText);
        lError.run();
        m_responseText = lError.getResponseText();
    }

    runResponse();
}

common_string server_http_socket_win_client::readData() {
    common_string lData;
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
            server_http_request_total lRequestTotal(lData);
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

void server_http_socket_win_client::sendData(const common_string& _data) {
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

void server_http_socket_win_client::runResponse() {
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

void server_http_socket_win_client::runError() {
    m_responseText = "Un problème a été rencontré.";
}

void server_http_socket_win_client::runSuccess() {
    m_responseText = "L'opération s'est déroulée avec success.";
}

#endif

