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
GTemplate GTemplate::create() {
    GTemplate lTemplate;
    return lTemplate;
}
//===============================================
GTemplate GTemplate::create(const GString& _templateRoot) {
    GTemplate lTemplate;
    lTemplate.setTemplateRoot(_templateRoot);
    return lTemplate;
}
//===============================================
GString GTemplate::parse(const GString& _filename) const {
    GString lPath = m_templateRoot + _filename;
    inja::Environment lEnv;
    inja::Template lTemplate = lEnv.parse_template(lPath.c_str());
    return lEnv.render(lTemplate, m_dataJson);
}
//===============================================
GString GTemplate::render(const GString& _templateText) const {
    inja::Environment lEnv;
    return lEnv.render(_templateText, m_dataJson);
}
//===============================================
void GTemplate::write(const GString& _filenameIn, const GString& _filenameOut) const {
    GString lPathIn = m_templateRoot + _filenameIn;
    GString lPathOut = m_templateRoot + _filenameOut;
    inja::Environment lEnv;
    inja::Template lTemplate = lEnv.parse_template(lPathIn.c_str());
    lEnv.write(lTemplate, m_dataJson, lPathOut.c_str());
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
