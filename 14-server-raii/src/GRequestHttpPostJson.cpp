//===============================================
#include "GRequestHttpPostJson.h"
#include "GResponseHttp.h"
//===============================================
GRequestHttpPostJson::GRequestHttpPostJson(const GString& _url, const GString& _dataJson)
: m_url         (_url)
, m_dataJson    (_dataJson) {
    m_responseType = rdv::RESPONSE_TYPE_JSON;
}
//===============================================
GRequestHttpPostJson::~GRequestHttpPostJson() {

}
//===============================================
void GRequestHttpPostJson::run() {
    if(m_url == "/callback/test/tree") {
        runTree();
    }
    else {
        slog(eGERR, "L'URL de la requête n'est pas gérée."
        "|url=%s", m_url.c_str());
        m_errors.addProblem();
    }
    runResponse();
}
//===============================================
void GRequestHttpPostJson::runTree() {
    nlohmann::json lJson = nlohmann::json::parse(m_dataJson.c_str());
    int i = 0;
    for(nlohmann::json::iterator it = lJson.begin(); it != lJson.end(); ++it) {
        std::cout << ++i << '\n';
    }
    //m_responseData = lJson.dump();
}
//===============================================
void GRequestHttpPostJson::runResponse() {
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
void GRequestHttpPostJson::runError() {
    nlohmann::json lJson;
    lJson["status"] = "error";
    lJson["msg"] = "Un problème a été rencontré.";
    m_responseData = lJson.dump();
}
//===============================================
void GRequestHttpPostJson::runSuccess() {
    nlohmann::json lJson;
    lJson["status"] = "success";
    lJson["msg"] = "L'opération s'est déroulée avec success.";
    m_responseData = lJson.dump();
}
//===============================================
