#pragma once

#include "common_string.h"
#include "common_enum.h"

GENUM_DEFINE(
    common_log_type
    , LOG_TYPE_OFF
    , LOG_TYPE_INF
    , LOG_TYPE_ERR
)

#define eGOFF   LOG_TYPE_OFF, "OFF", __FILE__, __LINE__, __FUNCTION__
#define eGINF   LOG_TYPE_INF, "INF", __FILE__, __LINE__, __FUNCTION__
#define eGERR   LOG_TYPE_ERR, "ERR", __FILE__, __LINE__, __FUNCTION__

class common_log {
public:
    common_log();
    ~common_log();
    void operator()(int _level, const char* _name, const char* _file, int _line, const char* _func, const char* _format, ...) const;

private:
    common_string getDate(const common_string& _format) const;
    common_string getFormat(const char* _format, ...) const;
};
