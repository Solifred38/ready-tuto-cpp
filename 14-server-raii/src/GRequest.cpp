//===============================================
#include "GRequest.h"
#include "GRequestHttp.h"
//===============================================
GRequest::GRequest(const GString& _requestText)
: m_requestText(_requestText) {

}
//===============================================
GRequest::~GRequest() {

}
//===============================================
void GRequest::run() {
    if(m_requestText.startsWith("GET")) {
        GRequestHttp lRequest(m_requestText);
        lRequest.run();
    }
    else {
        slog(eGERR, "La requête n'est pas gérée");
    }
}
//===============================================
