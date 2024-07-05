//===============================================
#pragma once
//===============================================
#include "GObject.h"
//===============================================
class GTemplate : public GObject {
public:
    GTemplate();
    GTemplate(const GTemplate& _obj);
    ~GTemplate();
    GTemplate render() const;

private:
    void renderInternal();

public:
    GTemplate& operator=(const GTemplate& _obj);
    nlohmann::json& operator[](const GString& _key);

public:
    void setTemplateRoot(const GString& _templateRoot)      {m_templateRoot = _templateRoot;}
    void setTemplateText(const GString& _templateText)      {m_templateText = _templateText;}
    const GString& getTemplateText()                        {return m_templateText;}

private:
    GString m_templateRoot;
    GString m_templateText;
    nlohmann::json m_dataJson;
};
//===============================================
