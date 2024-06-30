//===============================================
#include "GDispatchHttp.h"
#include "GResponseHttp.h"
//===============================================
GDispatchHttp::GDispatchHttp() {

}
//===============================================
GDispatchHttp::~GDispatchHttp() {

}
//===============================================
void GDispatchHttp::run() {
    if(m_requestHttp.getUri() == "/home") {
        runHome();
    }
    else if(m_requestHttp.getUri() == "/callback") {
        runCallback();
    }
    else {
        slog(eGERR, "L'uri HTTP n'est pas supportée."
        "|method=%s", m_requestHttp.getUri().c_str());
        m_errors.addProblem();
    }
    runResponse();
}
//===============================================
void GDispatchHttp::runResponse() {
    if(m_responseData.empty()) {
        if(m_errors.hasErrors()) {
            runError();
        }
        else {
            runSuccess();
        }
    }

    GResponseHttp lResponseHttp;
    lResponseHttp.setResponseData(m_responseData);
    lResponseHttp.run();
    m_responseText = lResponseHttp.getResponseText();
}
//===============================================
void GDispatchHttp::runSuccess() {
    m_responseData = "<h1>L'opération s'est bien déroulée.</h1>";
}
//===============================================
void GDispatchHttp::runError() {
    m_responseData = "<h1>Un problème a été rencontré.</h1>";
}
//===============================================
void GDispatchHttp::runHome() {
    m_responseData = "<h1>Je suis dans le Home.</h1>";
}
//===============================================
void GDispatchHttp::runCallback() {
    m_responseData = "<h1>Je suis dans le callback.</h1>";
}
//===============================================
