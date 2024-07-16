#include "server_http_request_error.h"
#include "server_http_response_http.h"

server_http_request_error::server_http_request_error(const common_string& _requestText)
: m_requestText(_requestText) {

}

server_http_request_error::~server_http_request_error() {

}

void server_http_request_error::run() {
    if(m_requestText.startsWith("GET")) {
        runHttp();
    }
}

void server_http_request_error::runHttp() {
    m_responseData = "Un problème a été rencontré.";
    server_http_response_http lResponseHttp(m_responseData, m_responseType, m_responseStatus);
    lResponseHttp.run();
    m_responseText = lResponseHttp.getResponseText();
}

