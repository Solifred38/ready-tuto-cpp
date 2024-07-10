//===============================================
#pragma once
//===============================================
#include "GObject.h"
//===============================================
class GTemplate : public GObject {
public:
    GTemplate();
    ~GTemplate();
    GString parse(const GString& _filename);
    GString render(const GString& _data);

public:
    GTemplate& operator=(const GTemplate& _obj);
    nlohmann::json& operator[](const GString& _key);

public:
    void setTemplateRoot(const GString& _templateRoot)      {m_templateRoot = _templateRoot;}

private:
    GString m_templateRoot;
    nlohmann::json m_dataJson;
};
//===============================================
