//===============================================
#include "GReplace.h"
//===============================================
GReplace::GReplace() {

}
//===============================================
GReplace::GReplace(const GString& _replaceText)
: m_replaceText(_replaceText) {

}
//===============================================
GReplace::~GReplace() {

}
//===============================================
void GReplace::run() {
    int lCount = m_replaceText.countMatch("\\{\\{\\w+\\}\\}");
    m_resultText = m_replaceText;

    for(int i = 0; i < lCount; i++) {
        GString lPattern = m_replaceText.searchMatch("\\{\\{(\\w+)\\}\\}", i, 0);
        GString lName = m_replaceText.searchMatch("\\{\\{(\\w+)\\}\\}", i, 1);
        m_patternMap[lName] = lPattern;
    }

    std::map<GString, GString>::iterator it;
    for(it = m_patternMap.begin(); it != m_patternMap.end(); it++) {
        GString lName = it->first;
        GString lPattern = it->second;
        GString lValue = m_replaceMap[lName];
        if(!lValue.empty()) {
            m_resultText = m_resultText.replaceAll(lPattern, lValue);
        }
    }
}
//===============================================
