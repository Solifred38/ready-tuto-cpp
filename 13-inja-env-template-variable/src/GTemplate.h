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
    GTemplate parse(const GString& _filename) const;
    GTemplate render() const;
    void write(const GString& _filenameIn, const GString& _filenameOut) const;

private:
    void parseInternal(const GString& _filename);
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
