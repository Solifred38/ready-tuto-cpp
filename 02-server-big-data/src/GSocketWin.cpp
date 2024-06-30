//===============================================
#include "GSocketWin.h"
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
        fprintf(stdout, "Erreur lors de l'initialisation de winsock2."
        "|msgErreur=%s"
        "\n", WSAGetLastError());
        return;
    }

    m_socket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

    if(m_socket == INVALID_SOCKET) {
        fprintf(stdout, "Erreur lors de la création du socket."
        "|msgErreur=%s"
        "\n", WSAGetLastError());
        WSACleanup();
        return;
    }

    sockaddr_in lAddressIn;
    lAddressIn.sin_family = AF_INET;
    lAddressIn.sin_addr.s_addr = inet_addr("0.0.0.0");
    lAddressIn.sin_port = htons(8080);

    if(bind(m_socket, reinterpret_cast<SOCKADDR*>(&lAddressIn), sizeof(lAddressIn)) == SOCKET_ERROR) {
        fprintf(stdout, "Erreur lors de la liaison du socket à l'adresse."
        "|msgErreur=%s"
        "\n", WSAGetLastError());
        closeServer();
        return;
    }

    if (listen(m_socket, 10) == SOCKET_ERROR) {
        fprintf(stdout, "Erreur lors de l'initialisation du nombre de connexions."
        "|msgErreur=%s"
        "\n", WSAGetLastError());
        closeServer();
        return;
    }

    fprintf(stdout, "Démarrage du serveur...\n");

    GSocketWin* lClient = new GSocketWin;
    lClient->m_socket = accept(m_socket, nullptr, nullptr);

    if (lClient->m_socket == SOCKET_ERROR) {
        fprintf(stdout, "Erreur lors de l'acceptation d'une connexion."
        "|msgErreur=%s"
        "\n", WSAGetLastError());
        closeServer();
        return;
    }

    GString lRequest = lClient->readData();

    fprintf(stdout, "La réception de la requête du client."
    "|data=%s"
    "\n", lRequest.c_str());

    std::string lResponseData = "<h1>Bonjour tout le monde.</h1>";

    std::stringstream lResponseHttp;
    lResponseHttp << "HTTP/1.1 200 OK" << std::endl;
    lResponseHttp << "Content-Type: text/html; charset=UTF-8" << std::endl;
    lResponseHttp << "Content-Length: " << lResponseData.size() << std::endl;
    lResponseHttp << std::endl;
    lResponseHttp << lResponseData << std::endl;

    GString lResponseText = lResponseHttp.str();
    lClient->sendData(lResponseText);

    fprintf(stdout, "L'envoi de la requête du client."
    "|data=%s"
    "\n", lResponseText.c_str());

    closeClient();
    closeServer();
}
//===============================================
GString GSocketWin::readData() {
    GString lData;
    char lBuffer[SOCKET_BUFFER_MAX];

    while(1) {
        int lBytes = recv(m_socket, lBuffer, SOCKET_BUFFER_MAX, 0);

        if(lBytes == SOCKET_ERROR) {
            fprintf(stdout, "Erreur lors de lecture des données sur le socket."
            "|msgErreur=%s"
            "\n", WSAGetLastError());
            closeClient();
            break;
        }

        lBuffer[lBytes] = '\0';
        lData += lBuffer;

        u_long lBytesIO;
        if(ioctlsocket(m_socket, FIONREAD, &lBytesIO) == SOCKET_ERROR) {
            fprintf(stdout, "Erreur lors de lecture du nombre de données restantes sur le socket."
            "|msgErreur=%s"
            "\n", WSAGetLastError());
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
        fprintf(stdout, "Erreur lors de lecture des données sur le socket."
        "|msgErreur=%s"
        "\n", WSAGetLastError());
        closeClient();
        return;
    }
}
//===============================================
void GSocketWin::closeServer() {
    closesocket(m_socket);
    WSACleanup();
}
//===============================================
void GSocketWin::closeClient() {
    closesocket(m_socket);
}
//===============================================
#endif
//===============================================
