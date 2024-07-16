
#include "server_http_request_http_get.h"
#include "server_http_response_http.h"

server_http_request_http_get::server_http_request_http_get(const common_string& _url, const std::map<common_string, common_string>& _paramsMap)
: m_url         (_url)
, m_paramsMap   (_paramsMap) {

}

server_http_request_http_get::~server_http_request_http_get() {

}

void server_http_request_http_get::run() {
    if(m_url == "/test/html_tree") {
        runTree();
    }
    else if(loadResource()) {
        slog(eGERR, "Le chargement de la ressource est terminée."
        "|url=%s", m_url.c_str());
    }
    else {
        slog(eGERR, "L'URL de la requête n'est pas gérée."
        "|url=%s", m_url.c_str());
        m_errors.addProblem();
    }
    runResponse();
}

void server_http_request_http_get::runTree() {
    common_template lTemplate;
    m_responseData = lTemplate.parse("/private/test/html_tree/template/html_tree.html");
    m_errors.addErrors(lTemplate.getErrors());
}

bool server_http_request_http_get::loadResource() {
    common_resource lResource(m_url);
    lResource.run();
    m_errors.addErrors(lResource.getErrors());
    if(!m_errors.hasErrors()) {
        m_responseType = lResource.getResponseType();
        m_responseData = lResource.getResponseData();
    }
    return !m_errors.hasErrors();
}

void server_http_request_http_get::runResponse() {
    if(m_responseData.empty()) {
        if(m_errors.hasErrors()) {
            runError();
        }
        else {
            runSuccess();
        }
    }
    server_http_response_http lResponseHttp(m_responseData, m_responseType, m_responseStatus);
    lResponseHttp.run();
    m_responseText = lResponseHttp.getResponseText();
}

void server_http_request_http_get::runError() {
    m_responseData = "Un problème a été rencontré.";
}

void server_http_request_http_get::runSuccess() {
    m_responseData = "L'opération s'est déroulée avec success.";
}
