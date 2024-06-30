//===============================================
#pragma once
//===============================================
#include "GString.h"
//===============================================
class GReplace {
public:
    GReplace();
    GReplace(const GString& _replaceText);
    ~GReplace();
    void run();

public:
    void addReplace(const GString& _key, const GString& _value)     {m_replaceMap[_key] = _value;}
    void setReplaceText(const GString& _replaceText)                {m_replaceText = _replaceText;}
    const GString& getResultText()                                  {return m_resultText;}

private:
    GString m_replaceText;
    GString m_resultText;
    std::map<GString, GString> m_replaceMap;
    std::map<GString, GString> m_patternMap;
};
//===============================================
