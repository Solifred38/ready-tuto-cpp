//===============================================
#pragma once
//===============================================
#include "GInclude.h"
#include "GString.h"
#include "GError.h"
#include "GLog.h"
#include "GMap.h"
#include "GResponseHttpStatus.h"
//===============================================
class GObject {
public:
    GObject();
    virtual ~GObject();

public:
    const GError& getErrors() const             {return m_errors;}
    const GString& getResponseType()            {return m_responseType;}
    const GString& getResponseData() const      {return m_responseData;}
    const GString& getResponseText() const      {return m_responseText;}

protected:
    GError m_errors;
    GLog slog;
    eGResponseHttpStatus m_responseStatus;
    GString m_responseType;
    GString m_responseData;
    GString m_responseText;
};
//===============================================
