#pragma once

#include "common_enum.h"
#include "common_string.h"
#include "common_error.h"
#include "common_log.h"

class common_object {
public:
    common_object();
    virtual ~common_object();

public:
    const common_error& getErrors() const    {return m_errors;}

protected:
    common_error m_errors;
    common_log slog;
};

