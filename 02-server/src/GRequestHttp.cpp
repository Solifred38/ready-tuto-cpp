//===============================================
#include "GRequestHttp.h"
//===============================================
GRequestHttp::GRequestHttp() {

}
//===============================================
GRequestHttp::GRequestHttp(const GRequestHttp& _obj) {
    *this = _obj;
}
//===============================================
GRequestHttp::~GRequestHttp() {

}
//===============================================
void GRequestHttp::run() {
    if(m_requestText.empty()) return;

    const GString CRLF = "\r\n";
    const GString CRLFCRLF = "\r\n\r\n";
    const GString SPACE = " ";
    const GString DOUBLE_POINT = ":";
    const GString QUESTION_POINT = "?";

    // POST /home/admin HTTP/1.1
    GString lData = m_requestText.extractSep(CRLF, 0);
    m_method = lData.extractSep(SPACE, 0);
    m_uri = lData.extractSep(SPACE, 1);
    m_version = lData.extractSep(SPACE, 2);

}
//===============================================
GRequestHttp& GRequestHttp::operator=(const GRequestHttp& _onj) {
    m_method    = _onj.m_method;
    m_uri       = _onj.m_uri;
    m_version   = _onj.m_version;
    return *this;
}
//===============================================
bool GRequestHttp::isGet() const {
    return (m_method == rdv::HTTP_REQUEST_GET);
}
//===============================================
bool GRequestHttp::isPost() const {
    return (m_method == rdv::HTTP_REQUEST_POST);
}
//===============================================
bool GRequestHttp::isHttp() const {
    if(isGet() || isPost()) return true;
    return false;
}
//===============================================
