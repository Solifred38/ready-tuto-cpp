//===============================================
#include "GServerWin.h"
//===============================================
#ifdef _WIN32
//===============================================
GSocketWin::GSocketWin() {

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

    SOCKET lSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

    if(lSocket == INVALID_SOCKET) {
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

    if(bind(lSocket, reinterpret_cast<SOCKADDR*>(&lAddressIn), sizeof(lAddressIn)) == SOCKET_ERROR) {
        fprintf(stdout, "Erreur lors de la liaison du socket à l'adresse."
        "|msgErreur=%s"
        "\n", WSAGetLastError());
        closesocket(lSocket);
        WSACleanup();
        return;
    }

    if (listen(lSocket, 10) == SOCKET_ERROR) {
        fprintf(stdout, "Erreur lors de l'initialisation du nombre de connexions."
        "|msgErreur=%s"
        "\n", WSAGetLastError());
        closesocket(lSocket);
        WSACleanup();
        return;
    }

    fprintf(stdout, "Démarrage du serveur...\n");

    SOCKET lClient = accept(lSocket, nullptr, nullptr);

    if (lClient == SOCKET_ERROR) {
        fprintf(stdout, "Erreur lors de l'acceptation d'une connexion."
        "|msgErreur=%s"
        "\n", WSAGetLastError());
        closesocket(lSocket);
        WSACleanup();
        return;
    }

    char lBuffer[SOCKET_BUFFER_MAX];
    int lBytes = recv(lClient, lBuffer, SOCKET_BUFFER_MAX, 0);

    if(lBytes == SOCKET_ERROR) {
        fprintf(stdout, "Erreur lors de lecture des données sur le socket."
        "|msgErreur=%s"
        "\n", WSAGetLastError());
        closesocket(lClient);
        closesocket(lSocket);
        WSACleanup();
        return;
    }

    lBuffer[lBytes] = '\0';
    fprintf(stdout, "La réception de la requête du client."
    "|data=%s"
    "\n", lBuffer);

    std::string lResponseData = "<h1>Bonjour tout le monde.</h1>";

    std::stringstream lResponseHttp;
    lResponseHttp << "HTTP/1.1 200 OK" << std::endl;
    lResponseHttp << "Content-Type: text/html; charset=UTF-8" << std::endl;
    lResponseHttp << "Content-Length: " << lResponseData.size() << std::endl;
    lResponseHttp << std::endl;
    lResponseHttp << lResponseData << std::endl;

    std::string lResponseText = lResponseHttp.str();

    lBytes = send(lClient, lResponseText.c_str(), lResponseText.size(), 0);

    if(lBytes == SOCKET_ERROR) {
        fprintf(stdout, "Erreur lors de lecture des données sur le socket."
        "|msgErreur=%s"
        "\n", WSAGetLastError());
        closesocket(lClient);
        closesocket(lSocket);
        WSACleanup();
        return;
    }

    fprintf(stdout, "L'envoi de la requête du client."
    "|data=%s"
    "\n", lResponseText.c_str());

    closesocket(lClient);
    closesocket(lSocket);
    WSACleanup();
}
//===============================================
#endif
//===============================================
