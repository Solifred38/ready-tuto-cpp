//===============================================
#include "GTemplate.h"
#include "GFile.h"
#include "GReplace.h"
//===============================================
GTemplate::GTemplate()
: m_templateRoot("../web") {

}
//===============================================
GTemplate::GTemplate(const GString& _filename)
: m_templateRoot    ("../web")
, m_filename        (_filename) {

}
//===============================================
GTemplate::GTemplate(const GTemplate& _obj) {
    *this = _obj;
}
//===============================================
GTemplate::~GTemplate() {

}
//===============================================
GTemplate GTemplate::parse() {
    GTemplate lTemplate = *this;
    lTemplate.parseInternal();
    m_errors.addErrors(lTemplate.getErrors());
    return lTemplate;
}
//===============================================
void GTemplate::parseInternal() {
    GString lPath = m_templateRoot + m_filename;
    GFile lFile(lPath);
    m_templateText = lFile.readBin();
    m_errors.addErrors(lFile.getErrors());
}
//===============================================
GTemplate GTemplate::render() {
    GTemplate lTemplate = *this;
    lTemplate.renderInternal();
    m_errors.addErrors(lTemplate.getErrors());
    return lTemplate;
}
//===============================================
void GTemplate::renderInternal() {
    GReplace lReplace(m_templateText);
    lReplace.setReplaceMap(m_replaceMap);
    m_templateText = lReplace.render().getReplaceText();
    m_errors.addErrors(lReplace.getErrors());
}
//===============================================
GTemplate& GTemplate::operator=(const GTemplate& _obj) {
    m_templateRoot  = _obj.m_templateRoot;
    m_filename      = _obj.m_filename;
    m_templateText  = _obj.m_templateText;
    m_replaceMap    = _obj.m_replaceMap;
    return *this;
}
//===============================================
void GTemplate::addReplaceArr(const GString& _key, const std::vector<GString>& _obj) {
    for(int i = 0; i < _obj.size(); i++) {
        GString lKey = _key + "." + GString(i + 1);
        GString lValue = _obj.at(i);
        m_replaceMap[lKey] = lValue;
    }
}
//===============================================
void GTemplate::addReplaceObj(const GString& _key, const std::map<GString, GString>& _obj) {
    std::map<GString, GString>::const_iterator it;
    for(it = _obj.begin(); it != _obj.end(); it++) {
        GString lKey = _key + "." + it->first;
        GString lValue = it->second;
        m_replaceMap[lKey] = lValue;
    }
}
//===============================================
