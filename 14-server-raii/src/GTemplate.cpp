//===============================================
#include "GTemplate.h"
//===============================================
GTemplate::GTemplate()
: m_templateRoot    ("../web") {

}
//===============================================
GTemplate::~GTemplate() {

}
//===============================================
GString GTemplate::parse(const GString& _filename) {
    GString lData;
    try {
        GString lPath = m_templateRoot + _filename;
        inja::Environment lEnv;
        inja::Template lTemplate = lEnv.parse_template(lPath.c_str());
        lData = lEnv.render(lTemplate, m_dataJson);
    }
    catch(const std::exception& e) {
        slog(eGERR, "L'exécution du moteur de template a échoué."
        "|msgErreur=%s", e.what());
        m_errors.addProblem();
    }
    return lData;
}
//===============================================
GString GTemplate::render(const GString& _data) {
    GString lData;
    try {
        inja::Environment lEnv;
        lData = lEnv.render(_data.c_str(), m_dataJson);
    }
    catch(const std::exception& e) {
        slog(eGERR, "L'exécution du moteur de template a échoué."
        "|msgErreur=%s", e.what());
        m_errors.addProblem();
    }
    return lData;
}
//===============================================
GTemplate& GTemplate::operator=(const GTemplate& _obj) {
    m_templateRoot  = _obj.m_templateRoot;
    m_dataJson      = _obj.m_dataJson;
    return *this;
}
//===============================================
nlohmann::json& GTemplate::operator[](const GString& _key) {
    return m_dataJson[_key.c_str()];
}
//===============================================
