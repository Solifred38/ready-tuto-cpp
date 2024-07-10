//===============================================
#include "GRequestTotal.h"
//===============================================
GRequestTotal::GRequestTotal(const GString& _requestText)
: m_requestText (_requestText)
, m_total       (0) {

}
//===============================================
GRequestTotal::~GRequestTotal() {

}
//===============================================
void GRequestTotal::run() {
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
//===============================================
void GRequestTotal::runHttp() {
    const GString CRLF      = "\r\n";
    const GString CRLFCRLF  = "\r\n\r\n";

    int lContentLenght      = m_requestText.extractSeps("Content-Length:", CRLF, 0).trim().toInt();
    GString lHeader         = m_requestText.extractSep(CRLFCRLF, 0);

    m_total = lHeader.size() + CRLFCRLF.size() + lContentLenght;
}
//===============================================
