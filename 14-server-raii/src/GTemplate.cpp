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
GString GTemplate::parse(const GString& _filename) const {
    GString lPath = m_templateRoot + _filename;
    inja::Environment lEnv;
    inja::Template lTemplate = lEnv.parse_template(lPath.c_str());
    return lEnv.render(lTemplate, m_dataJson);
}
//===============================================
GString GTemplate::render(const GString& _data) const {
    inja::Environment lEnv;
    return lEnv.render(_data.c_str(), m_dataJson);
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
