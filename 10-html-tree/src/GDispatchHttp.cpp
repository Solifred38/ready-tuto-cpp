//===============================================
#include "GDispatchHttp.h"
#include "GResponseHttp.h"
#include "GResource.h"
#include "GHome.h"
#include "GCallback.h"
//===============================================
GDispatchHttp::GDispatchHttp()
: m_responseType(rdv::RESPONSE_TYPE_HTML) {

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
    else if(loadResource()) {
        slog(eGINF, "Le chargement de la ressource est terminée."
        "|uri=%s", m_requestHttp.getUri().c_str());
    }
    else {
        slog(eGERR, "L'uri HTTP n'est pas supportée."
        "|method=%s", m_requestHttp.getUri().c_str());
        m_errors.addProblem();
    }
    runResponse();
}
//===============================================
bool GDispatchHttp::loadResource() {
    GResource lResource(m_requestHttp.getUri());
    lResource.run();
    m_errors.addErrors(lResource.getErrors());
    if(!m_errors.hasErrors()) {
        m_responseType = lResource.getResponseType();
        m_responseData = lResource.getResponseData();
    }
    return !m_errors.hasErrors();
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
    lResponseHttp.setResponseType(m_responseType);
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
    GHome lObj;
    lObj.run();
    m_responseData = lObj.getResponseData();
}
//===============================================
void GDispatchHttp::runCallback() {
    GCallback lObj;
    lObj.run();
    m_responseData = lObj.getResponseData();
}
//===============================================
