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
GTemplate GTemplate::render() const {
    GTemplate lTemplate = *this;
    lTemplate.renderInternal();
    return lTemplate;
}
//===============================================
void GTemplate::renderInternal() {
    inja::Environment lEnv;
    m_templateText = lEnv.render(m_templateText, m_dataJson);
}
//===============================================
GTemplate& GTemplate::operator=(const GTemplate& _obj) {
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
