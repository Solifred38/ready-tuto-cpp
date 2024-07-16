#include "server_http_request_total.h"

server_http_request_total::server_http_request_total(const common_string& _requestText)
: m_requestText (_requestText)
, m_total       (0) {

}

server_http_request_total::~server_http_request_total() {

}

void server_http_request_total::run() {
    if(m_requestText.startsWith("GET")) {
        runHttp();
    }
    else if(m_requestText.startsWith("POST")) {
        runHttp();
    }
    else {
        m_total = m_requestText.size();
    }
}

void server_http_request_total::runHttp() {
    const common_string CRLF      = "\r\n";
    const common_string CRLFCRLF  = "\r\n\r\n";

    int lContentLenght      = m_requestText.extractSeps("Content-Length:", CRLF, 0).trim().toInt();
    common_string lHeader         = m_requestText.extractSep(CRLFCRLF, 0);

    m_total = lHeader.size() + CRLFCRLF.size() + lContentLenght;
}
