//===============================================
#include "GReplace.h"
#include "GTemplate.h"
//===============================================
GReplace::GReplace() {

}
//===============================================
GReplace::GReplace(const GString& _replaceText)
: m_replaceText(_replaceText) {

}
//===============================================
GReplace::GReplace(const GReplace& _obj) {
    *this = _obj;
}
//===============================================
GReplace::~GReplace() {

}
//===============================================
GReplace GReplace::render() {
    GReplace lReplace = *this;
    lReplace.runForInternal();
    lReplace.runDataInternal();
    m_errors.addErrors(lReplace.getErrors());
    return lReplace;
}
//===============================================
void GReplace::runDataInternal() {
    int lCount = m_replaceText.countMatch("\\{\\{\\w+(\\.?\\w+)*\\}\\}");

    for(int i = 0; i < lCount; i++) {
        GString lPattern = m_replaceText.searchMatch("\\{\\{(\\w+(\\.?\\w+)*)\\}\\}", i, 0);
        GString lName = m_replaceText.searchMatch("\\{\\{(\\w+(\\.?\\w+)*)\\}\\}", i, 1);
        m_patternMap[lName] = lPattern;
    }

    std::map<GString, GString>::iterator it;
    for(it = m_patternMap.begin(); it != m_patternMap.end(); it++) {
        GString lName = it->first;
        GString lPattern = it->second;
        GString lValue = m_replaceMap[lName];
        if(lValue.empty()) {
            slog(eGERR, "La variable du template n'a été trouvée."
            "|pattern=%s", lPattern.c_str());
            m_errors.addProblem();
        }
        else {
            m_replaceText = m_replaceText.replaceAll(lPattern, lValue);
        }
    }
}
//===============================================
void GReplace::runForInternal() {
    runLoopForInternal();
}
//===============================================
void GReplace::runLoopForInternal() {
    int lCount = m_replaceText.countMatch("\\{\\{\\w+([\\.\\s]?\\w+)*\\}\\}");
    int lCountFor = 0;
    int lCurPos = 0;
    int lCurPatternSize = 0;
    int lForPos = 0;
    GString lForText;
    int lForTextPos = 0;
    int lForTextSize = 0;
    int lForReplaceSize = 0;
    GString lForPatternText;
    int lForPatternSize = 0;
    int lEndForPos = 0;

    for(int i = 0; i < lCount; i++) {
        GString lPattern = m_replaceText.searchMatch("\\{\\{(\\w+([\\.\\s]?\\w+)*)\\}\\}", i, 0);
        GString lName = m_replaceText.searchMatch("\\{\\{(\\w+([\\.\\s]?\\w+)*)\\}\\}", i, 1);
        m_patternMap[lName] = lPattern;
        lCurPos = m_replaceText.indexOf(lPattern, lCurPos);
        lCurPatternSize = lPattern.size();

        if(lName.startsWith("for ")) {
            lCountFor++;
            if(lCountFor == 1) {
                lForPos = lCurPos;
                lForPatternSize = lCurPatternSize;
                lForPatternText = lName;
            }
        }
        else if(lName == "endfor") {
            lCountFor--;
            if(lCountFor == 0) {
                lEndForPos = lCurPos;
                lForTextPos = lForPos + lForPatternSize;
                lForTextSize = lEndForPos - lForTextPos;
                lForReplaceSize = lForTextSize + lCurPatternSize + lForPatternSize;
                lForText = m_replaceText.substr(lForTextPos, lForTextSize);
            }
        }

        if(!lForPatternText.empty() && !lForText.empty()) {
            GString lForPattern = lForPatternText.searchMatch("(\\w+) in (\\w+)", 0, 0);
            GString lForName    = lForPatternText.searchMatch("(\\w+) in (\\w+)", 0, 1);
            GString lForMap     = lForPatternText.searchMatch("(\\w+) in (\\w+)", 0, 2);

            GReplace lForReplace;
            lForReplace.setReplaceMap(m_replaceMap);
            lForReplace.setReplaceText(lForText);
            lForReplace.setForItemName(lForName);
            lForReplace.setForMapName(lForMap);
            lForReplace.renderForInternal();

            GReplaceFor lReplaceFor;
            lReplaceFor.m_pos       = lForPos;
            lReplaceFor.m_size      = lForReplaceSize;
            lReplaceFor.m_text      = lForReplace.getReplaceText();
            m_replaceFor.push_back  (lReplaceFor);

            lForPatternText = "";
            lForText = "";
        }

        lCurPos += lPattern.size();
    }

    replaceForInternal();

    if(m_replaceText.countMatch("\\{\\{for (.*) in (.*)\\}\\}")) {
        m_replaceFor.clear();
        runLoopForInternal();
    }
}
//===============================================
void GReplace::renderForInternal() {
    std::map<GString, GString>::iterator it;
    GString lForText;
    int lIndex = 0;
    int lIndex1 = 0;
    for(it = m_replaceMap.begin(); it != m_replaceMap.end(); it++) {
        GString lKey = it->first;
        GString lValue = it->second;
        if(lKey.isMatch(m_forMapName + "." + "\\d")) {
            GReplace lReplace = *this;
            lReplace.addReplaceData(m_forItemName, lValue);
            lReplace.addReplaceData("loop.index", lIndex++);
            lReplace.addReplaceData("loop.index1", ++lIndex1);
            lReplace.runDataInternal();
            lForText += lReplace.getReplaceText();
        }
    }
    m_replaceText = lForText;
}
//===============================================
void GReplace::replaceForInternal() {
    std::vector<GReplaceFor>::iterator it;
    int lDiff = 0;

    for(it = m_replaceFor.begin(); it != m_replaceFor.end(); it++) {
        int lPos = it->m_pos + lDiff;
        int lSize = it->m_size;
        GString lText = it->m_text;
        lDiff += lText.size() - lSize;

        m_replaceText = m_replaceText.replace(lPos, lSize, lText);
    }
}
//===============================================
GReplace& GReplace::operator=(const GReplace& _obj) {
    m_replaceText   = _obj.m_replaceText;
    m_replaceMap    = _obj.m_replaceMap;
    m_patternMap    = _obj.m_patternMap;
    m_forItemName   = _obj.m_forItemName;
    m_forMapName    = _obj.m_forMapName;
    m_replaceFor    = _obj.m_replaceFor;
    return *this;
}
//===============================================
