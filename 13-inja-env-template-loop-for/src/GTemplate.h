//===============================================
#pragma once
//===============================================
#include "GObject.h"
//===============================================
class GTemplate : public GObject {
private:
    GTemplate();

public:
    GTemplate(const GTemplate& _obj);
    ~GTemplate();
    static GTemplate create();
    static GTemplate create(const GString& _templateRoot);
    GString parse(const GString& _filename) const;
    GString render(const GString& _templateText) const;
    void write(const GString& _filenameIn, const GString& _filenameOut) const;

public:
    GTemplate& operator=(const GTemplate& _obj);
    nlohmann::json& operator[](const GString& _key);

public:
    void setTemplateRoot(const GString& _templateText)      {m_templateText = _templateText;}
    const GString& getTemplateText()                        {return m_templateText;}

private:
    GString m_templateRoot;
    GString m_templateText;
    nlohmann::json m_dataJson;
};
//===============================================
