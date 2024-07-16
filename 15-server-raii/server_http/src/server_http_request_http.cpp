#include "server_http_request_http.h"
#include "server_http_request_http_get.h"
#include "server_http_request_http_post_json.h"

server_http_request_http::server_http_request_http(const common_string& _requestText)
: m_requestText(_requestText) {

}

server_http_request_http::~server_http_request_http() {

}

void server_http_request_http::run() {
    const common_string CRLF = "\r\n";
    const common_string CRLFCRLF = "\r\n\r\n";
    const common_string SPACE = " ";
    const common_string DOUBLE_POINT = ":";
    const common_string QUESTION_POINT = "?";

    // POST /home/admin HTTP/1.1
    common_string lData           = m_requestText.extractSep(CRLF, 0);
    common_string lMethod         = lData.extractSep(SPACE, 0);
    common_string lUri            = lData.extractSep(SPACE, 1);
    common_string lVersion        = lData.extractSep(SPACE, 2);

    // /home/admin?key1=value1&key2=value2
    common_string lUrl            = lUri.extractSep(QUESTION_POINT, 0);
    common_string lQueryString    = lUri.extractSep(QUESTION_POINT, 1);

    // Host: 192.168.1.8:9050
    common_string lHost           = m_requestText.extractSeps("Host:", CRLF).trim();
    // Connection: keep-alive
    common_string lConnection     = m_requestText.extractSeps("Connection:", CRLF).trim();
    // Content-Length: 1625
    int lContentLength      = m_requestText.extractSeps("Content-Length:", CRLF).trim().toInt();
    // Cache-Control: max-age=0
    common_string lCacheControl   = m_requestText.extractSeps("Cache-Control:", CRLF).trim();
    // Upgrade-Insecure-Requests: 1
    common_string lUpgradeInsecureRequests = m_requestText.extractSeps("Upgrade-Insecure-Requests:", CRLF).trim();
    // Origin: http://192.168.1.8:9050
    common_string lOrigin         = m_requestText.extractSeps("Origin:", CRLF).trim();
    // Content-Type: application/x-www-form-urlencoded
    common_string lContentType    = m_requestText.extractSeps("Content-Type:", CRLF).trim();
    // User-Agent: Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/120.0.0.0 Safari/537.36
    common_string lUserAgent      = m_requestText.extractSeps("User-Agent:", CRLF).trim();
    // Accept: text/html,application/xhtml+xml,application/xml;q=0.9,image/avif,image/webp,image/apng,*/*;q=0.8,application/signed-exchange;v=b3;q=0.7
    common_string lAccept         = m_requestText.extractSeps("Accept:", CRLF).trim();
    // Referer: http://192.168.1.8:9050/carpool/inscription/email
    common_string lReferer        = m_requestText.extractSeps("Referer:", CRLF).trim();
    // Accept-Encoding: gzip, deflate
    common_string lAcceptEncoding = m_requestText.extractSeps("Accept-Encoding:", CRLF).trim();
    // Accept-Language: fr-FR,fr;q=0.9,en-US;q=0.8,en;q=0.7,zh-CN;q=0.6,zh;q=0.5
    common_string lAcceptLanguage = m_requestText.extractSeps("Accept-Language:", CRLF).trim();
    // request
    common_string lRequestData    = m_requestText.extractEnd(CRLFCRLF, 0);

    slog(eGINF, "L'analyse de la requête HTTP est terminée."
    "|method=%s"
    "|uri=%s"
    "|version=%s"
    "|url=%s"
    "|queryString=%s"
    "|host=%s"
    "|connection=%s"
    "|contentLength=%d"
    "|cacheControl=%s"
    "|upgradeInsecureRequests=%s"
    "|origin=%s"
    "|contentType=%s"
    "|userAgent=%s"
    "|accept=%s"
    "|referer=%s"
    "|acceptEncoding=%s"
    "|acceptLanguage=%s"
    "|requestData=%s"
    , lMethod.c_str(), lUri.c_str(), lVersion.c_str(), lUrl.c_str(), lQueryString.c_str()
    , lHost.c_str(), lConnection.c_str(), lContentLength, lCacheControl.c_str(), lUpgradeInsecureRequests.c_str()
    , lOrigin.c_str(), lContentType.c_str(), lUserAgent.c_str(), lAccept.c_str(), lReferer.c_str(), lAcceptEncoding.c_str()
    , lAcceptLanguage.c_str(), lRequestData.limit(100).c_str());

    if(lMethod == "GET") {
        server_http_request_http_get lRequest(lUrl, getParamsMap(lQueryString));
        lRequest.run();
        m_errors.addErrors(lRequest.getErrors());
        m_responseText = lRequest.getResponseText();
    }
    else if(lMethod == "POST") {
        if(lContentType == rdv::REQUEST_TYPE_JSON) {
            server_http_request_http_post_json lRequest(lUrl, lRequestData);
            lRequest.run();
            m_errors.addErrors(lRequest.getErrors());
            m_responseText = lRequest.getResponseText();
        }
        else {
            slog(eGERR, "Le contentType de la requête n'est pas géré."
            "|contentType=%s", lContentType.c_str());
            m_errors.addProblem();
        }
    }
    else {
        slog(eGERR, "La méthode HTTP n'est pas gérée."
        "|method=%s", lMethod.c_str());
        m_errors.addProblem();
    }
}

std::map<common_string, common_string> server_http_request_http::getParamsMap(const common_string& _paramsText) const {
    std::map<common_string, common_string> lParamsMap;
    const common_string SIGN_EQU = "=";
    const common_string SIGN_AND = "&";
    int lCount = _paramsText.countSep(SIGN_AND);
    for(int i = 0; i < lCount; i++) {
        common_string lData       = _paramsText.extractSep(SIGN_AND, i);
        common_string lKey        = lData.extractSep(SIGN_EQU, 0);
        common_string lValue      = lData.extractSep(SIGN_EQU, 1);
        lParamsMap[lKey]    = lValue;
    }
    return lParamsMap;
}

