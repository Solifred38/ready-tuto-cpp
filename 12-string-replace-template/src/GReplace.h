//===============================================
#pragma once
//===============================================
#include "GObject.h"
//===============================================
class GReplace : public GObject {
public:
    GReplace();
    GReplace(const GString& _replaceText);
    ~GReplace();
    void run();

public:
    void setReplaceText(const GString& _replaceText)                    {m_replaceText = _replaceText;}
    void setReplaceMap(const std::map<GString, GString>& _replaceMap)   {m_replaceMap = _replaceMap;}
    const GString& getResultText()                                      {return m_resultText;}

private:
    GString m_replaceText;
    GString m_resultText;
    std::map<GString, GString> m_replaceMap;
    std::map<GString, GString> m_patternMap;
};
//===============================================
