//===============================================
#include "GRequestHttpGet.h"
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
    if(m_url == "test") {

    }
    else {
        slog(eGERR, "L'URL de la méthode n'est pas gérée."
        "|url=%s", m_url.c_str());
    }
}
//===============================================
