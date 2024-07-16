
#include "server_http_request.h"
#include "server_http_request_http.h"

server_http_request::server_http_request(const common_string& _requestText)
: m_requestText(_requestText) {

}

server_http_request::~server_http_request() {

}

void server_http_request::run() {
    if(m_requestText.startsWith("GET")) {
        server_http_request_http lRequest(m_requestText);
        lRequest.run();
        m_errors.addErrors(lRequest.getErrors());
        m_responseText = lRequest.getResponseText();
    }
    else if(m_requestText.startsWith("POST")) {
        server_http_request_http lRequest(m_requestText);
        lRequest.run();
        m_errors.addErrors(lRequest.getErrors());
        m_responseText = lRequest.getResponseText();
    }
    else {
        slog(eGERR, "La requête n'est pas gérée.");
        m_errors.addProblem();
    }
}

