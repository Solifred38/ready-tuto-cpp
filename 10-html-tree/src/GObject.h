//===============================================
#pragma once
//===============================================
#include "GInclude.h"
#include "GString.h"
#include "GEnum.h"
#include "GMap.h"
#include "GError.h"
#include "GLog.h"
//===============================================
class GObject {
public:
    GObject();
    virtual ~GObject();

public:
    const GError& getErrors() const     {return m_errors;}

protected:
    GError m_errors;
    GLog slog;
};
//===============================================
