//===============================================
#include "GRequestHttpGet.h"
#include "GResponseHttp.h"
#include "GResource.h"
#include "GHome.h"
//===============================================
GRequestHttpGet::GRequestHttpGet(const GString& _url, const std::map<GString, GString>& _paramsMap)
: m_url         (_url)
, m_paramsMap   (_paramsMap) {

}
//===============================================
GRequestHttpGet::~GRequestHttpGet() {

}
//===============================================
void GRequestHttpGet::run() {
    if(m_url == "/test") {
        runHome();
    }
    else if(loadResource()) {
        slog(eGERR, "Le chargement de la ressource est terminée."
        "|url=%s", m_url.c_str());
    }
    else {
        slog(eGERR, "L'URL de la méthode n'est pas gérée."
        "|url=%s", m_url.c_str());
        m_errors.addProblem();
    }
    runResponse();
}
//===============================================
void GRequestHttpGet::runHome() {
    GHome lHome;
    lHome.run();
    m_responseData = lHome.getResponseData();
}
//===============================================
bool GRequestHttpGet::loadResource() {
    GResource lResource(m_url);
    lResource.run();
    m_errors.addErrors(lResource.getErrors());
    m_responseType = lResource.getResponseType();
    m_responseData = lResource.getResponseData();
    return !m_errors.hasErrors();
}
//===============================================
void GRequestHttpGet::runResponse() {
    if(m_responseData.empty()) {
        if(m_errors.hasErrors()) {
            runError();
        }
        else {
            runSuccess();
        }
    }
    GResponseHttp lResponseHttp(m_responseData, m_responseType, m_responseStatus);
    lResponseHttp.run();
    m_responseText = lResponseHttp.getResponseText();
}
//===============================================
void GRequestHttpGet::runError() {
    m_responseData = "Un problème a été rencontré.";
}
//===============================================
void GRequestHttpGet::runSuccess() {
    m_responseData = "L'opération s'est déroulée avec success.";
}
//===============================================
