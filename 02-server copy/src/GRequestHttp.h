//===============================================
#pragma once
//===============================================
#include "GObject.h"
//===============================================
class GRequestHttp {
public:
    GRequestHttp();
    GRequestHttp(const GRequestHttp& _obj);
    ~GRequestHttp();
    void run();
    bool isGet() const;
    bool isPost() const;
    bool isHttp() const;

public:
    void setRequestText(const GString& _requestText)        {m_requestText = _requestText;}
    void setMethod(const GString& _method)                  {m_method = _method;}
    void setUri(const GString& _uri)                        {m_uri = _uri;}
    void setVersion(const GString& _version)                {m_version = _version;}

    const GString& getMethod() const                        {return m_method;}
    const GString& getUri() const                           {return m_uri;}
    const GString& getVersion() const                       {return m_version;}

    GRequestHttp& operator=(const GRequestHttp& _onj);

private:
    GString m_requestText;
    GString m_method;
    GString m_uri;
    GString m_version;
};
//===============================================
