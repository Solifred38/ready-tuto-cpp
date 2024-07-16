#include "server_http_request_http_post_json.h"
#include "server_http_response_http.h"

server_http_request_http_post_json::server_http_request_http_post_json(const common_string& _url, const common_string& _dataJson)
: m_url         (_url)
, m_dataJson    (_dataJson) {
    m_responseType = rdv::RESPONSE_TYPE_JSON;
}

server_http_request_http_post_json::~server_http_request_http_post_json() {

}

void server_http_request_http_post_json::run() {
    if(m_url == "/callback/test/html_tree") {
        runTree();
    }
    else {
        slog(eGERR, "L'URL de la requête n'est pas gérée."
        "|url=%s", m_url.c_str());
        m_errors.addProblem();
    }
    runResponse();
}

void server_http_request_http_post_json::runTree() {
    slog(eGERR, "ooooooooooooooooooooooooooooooooooooo (1)"
    "|data=%s", m_dataJson.c_str());
    /*GTreeCB lTree(m_dataJson);
    lTree.run();
    m_errors.addErrors(lTree.getErrors());*/
}

void server_http_request_http_post_json::runResponse() {
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

void server_http_request_http_post_json::runError() {
    nlohmann::json lJson;
    lJson["status"] = "error";
    lJson["msg"] = "Un problème a été rencontré.";
    m_responseData = lJson.dump();
}

void server_http_request_http_post_json::runSuccess() {
    nlohmann::json lJson;
    lJson["status"] = "success";
    lJson["msg"] = "L'opération s'est déroulée avec success.";
    m_responseData = lJson.dump();
}

