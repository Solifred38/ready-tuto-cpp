//===============================================
#include "GRequestHttp.h"
#include "GRequestHttpGet.h"
//===============================================
GRequestHttp::GRequestHttp(const GString& _requestText)
: m_requestText(_requestText) {

}
//===============================================
GRequestHttp::~GRequestHttp() {

}
//===============================================
void GRequestHttp::run() {
    const GString CRLF = "\r\n";
    const GString CRLFCRLF = "\r\n\r\n";
    const GString SPACE = " ";
    const GString DOUBLE_POINT = ":";
    const GString QUESTION_POINT = "?";

    // POST /home/admin HTTP/1.1
    GString lData           = m_requestText.extractSep(CRLF, 0);
    GString lMethod         = lData.extractSep(SPACE, 0);
    GString lUri            = lData.extractSep(SPACE, 1);
    GString lVersion        = lData.extractSep(SPACE, 2);

    // /home/admin?key1=value1&key2=value2
    GString lUrl            = lUri.extractSep(QUESTION_POINT, 0);
    GString lQueryString    = lUri.extractSep(QUESTION_POINT, 1);

    // Host: 192.168.1.8:9050
    GString lHost           = m_requestText.extractSeps("Host:", CRLF).trim();
    // Connection: keep-alive
    GString lConnection     = m_requestText.extractSeps("Connection:", CRLF).trim();
    // Cache-Control: max-age=0
    GString lCacheControl   = m_requestText.extractSeps("Cache-Control:", CRLF).trim();
    // Upgrade-Insecure-Requests: 1
    GString lUpgradeInsecureRequests = m_requestText.extractSeps("Upgrade-Insecure-Requests:", CRLF).trim();
    // Origin: http://192.168.1.8:9050
    GString lOrigin         = m_requestText.extractSeps("Origin:", CRLF).trim();
    // Content-Type: application/x-www-form-urlencoded
    GString lContentType    = m_requestText.extractSeps("Content-Type:", CRLF).trim();
    // User-Agent: Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/120.0.0.0 Safari/537.36
    GString lUserAgent      = m_requestText.extractSeps("User-Agent:", CRLF).trim();
    // Accept: text/html,application/xhtml+xml,application/xml;q=0.9,image/avif,image/webp,image/apng,*/*;q=0.8,application/signed-exchange;v=b3;q=0.7
    GString lAccept         = m_requestText.extractSeps("Accept:", CRLF).trim();
    // Referer: http://192.168.1.8:9050/carpool/inscription/email
    GString lReferer        = m_requestText.extractSeps("Referer:", CRLF).trim();
    // Accept-Encoding: gzip, deflate
    GString lAcceptEncoding = m_requestText.extractSeps("Accept-Encoding:", CRLF).trim();
    // Accept-Language: fr-FR,fr;q=0.9,en-US;q=0.8,en;q=0.7,zh-CN;q=0.6,zh;q=0.5
    GString lAcceptLanguage = m_requestText.extractSeps("Accept-Language:", CRLF).trim();
    // request
    GString lRequestData    = m_requestText.extractEnd(CRLFCRLF, 0);

    slog(eGINF, "L'analyse de la requête HTTP est terminée."
    "|method=%s"
    "|uri=%s"
    "|version=%s"
    "|url=%s"
    "|queryString=%s"
    "|host=%s"
    "|connection=%s"
    "|cacheControl=%s"
    "|upgradeInsecureRequests=%s"
    "|origin=%s"
    "|userAgent=%s"
    "|accept=%s"
    "|referer=%s"
    "|acceptEncoding=%s"
    "|acceptLanguage=%s"
    "|requestData=%s"
    , lMethod.c_str(), lUri.c_str(), lVersion.c_str(), lUrl.c_str(), lQueryString.c_str()
    , lHost.c_str(), lConnection.c_str(), lCacheControl.c_str(), lUpgradeInsecureRequests.c_str()
    , lOrigin.c_str(), lUserAgent.c_str(), lAccept.c_str(), lReferer.c_str(), lAcceptEncoding.c_str()
    , lAcceptLanguage.c_str(), lRequestData.c_str());

    if(lMethod == "GET") {
        GRequestHttpGet lRequest(lUrl, getParamsMap(lQueryString));
        lRequest.run();
    }
    else {
        slog(eGERR, "La méthode HTTP n'est pas gérée."
        "|method=%s", lMethod.c_str());
    }
}
//===============================================
std::map<GString, GString> GRequestHttp::getParamsMap(const GString& _paramsText) const {
    std::map<GString, GString> lParamsMap;
    const GString SIGN_EQU = "=";
    const GString SIGN_AND = "&";
    int lCount = _paramsText.countSep(SIGN_AND);
    for(int i = 0; i < lCount; i++) {
        GString lData       = _paramsText.extractSep(SIGN_AND, i);
        GString lKey        = lData.extractSep(SIGN_EQU, 0);
        GString lValue      = lData.extractSep(SIGN_EQU, 1);
        lParamsMap[lKey]    = lValue;
    }
    return lParamsMap;
}
//===============================================
