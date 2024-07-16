//===============================================
#include "GRequestError.h"
#include "GResponseHttp.h"
//===============================================
GRequestError::GRequestError(const GString& _requestText)
: m_requestText(_requestText) {

}
//===============================================
GRequestError::~GRequestError() {

}
//===============================================
void GRequestError::run() {
    if(m_requestText.startsWith("GET")) {
        runHttp();
    }
}
//===============================================
void GRequestError::runHttp() {
    m_responseData = "Un problème a été rencontré.";
    GResponseHttp lResponseHttp(m_responseData, m_responseType, m_responseStatus);
    lResponseHttp.run();
    m_responseText = lResponseHttp.getResponseText();
}
//===============================================
