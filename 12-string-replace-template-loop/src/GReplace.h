//===============================================
#pragma once
//===============================================
#include "GObject.h"
//===============================================
struct GReplaceFor {
    int m_pos;
    int m_size;
    GString m_text;
};
//===============================================
class GReplace : public GObject {
public:
    GReplace();
    GReplace(const GString& _replaceText);
    GReplace(const GReplace& _obj);
    ~GReplace();
    GReplace render();

private:
    void runDataInternal();
    void runLoopForInternal();
    void renderForInternal();
    void replaceForInternal();

public:
    void addReplaceData(const GString& _key, const GString& _value)     {m_replaceMap[_key] = _value;}
    void setReplaceText(const GString& _replaceText)                    {m_replaceText = _replaceText;}
    void setForItemName(const GString& _forItemName)                    {m_forItemName = _forItemName;}
    void setForMapName(const GString& _forMapName)                      {m_forMapName = _forMapName;}
    void setReplaceMap(const std::map<GString, GString>& _replaceMap)   {m_replaceMap = _replaceMap;}
    const GString& getReplaceText()                                     {return m_replaceText;}

public:
    GReplace& operator=(const GReplace& _obj);

private:
    GString m_replaceText;
    std::map<GString, GString> m_replaceMap;
    std::map<GString, GString> m_patternMap;
    GString m_forItemName;
    GString m_forMapName;
    std::vector<GReplaceFor> m_replaceFor;
};
//===============================================
