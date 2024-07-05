//===============================================
#include "GTemplate.h"
//===============================================
GTemplate::GTemplate()
: m_templateRoot("../web") {

}
//===============================================
GTemplate::GTemplate(const GTemplate& _obj) {
    *this = _obj;
}
//===============================================
GTemplate::~GTemplate() {

}
//===============================================
GTemplate GTemplate::parse() const {
    GTemplate lTemplate = *this;
    lTemplate.parseInternal();
    return lTemplate;
}
//===============================================
GTemplate GTemplate::render() const {
    GTemplate lTemplate = *this;
    lTemplate.renderInternal();
    return lTemplate;
}
//===============================================
void GTemplate::write(const GString& _filename) const {
    GString lPathIn = m_templateRoot + m_filename;
    GString lPathOut = m_templateRoot + _filename;
    inja::Environment lEnv;
    inja::Template lTemplate = lEnv.parse_template(lPathIn.c_str());
    lEnv.write(lTemplate, m_dataJson, lPathOut.c_str());
}
//===============================================
void GTemplate::parseInternal() {
    GString lPath = m_templateRoot + m_filename;
    inja::Environment lEnv;
    inja::Template lTemplate = lEnv.parse_template(lPath.c_str());
    m_templateText = lEnv.render(lTemplate, m_dataJson);
}
//===============================================
void GTemplate::renderInternal() {
    inja::Environment lEnv;
    m_templateText = lEnv.render(m_templateText, m_dataJson);
}
//===============================================
GTemplate& GTemplate::operator=(const GTemplate& _obj) {
    m_filename      = _obj.m_filename;
    m_templateRoot  = _obj.m_templateRoot;
    m_templateText  = _obj.m_templateText;
    m_dataJson      = _obj.m_dataJson;
    return *this;
}
//===============================================
nlohmann::json& GTemplate::operator[](const GString& _key) {
    return m_dataJson[_key.c_str()];
}
//===============================================
