//===============================================
#pragma once
//===============================================
#include "GInclude.h"
#include "GEnum.h"
//===============================================
GENUM_DEFINE(
    eGLogType
    , LOG_TYPE_OFF
    , LOG_TYPE_INF
    , LOG_TYPE_ERR
)
//===============================================
#define eGOFF   LOG_TYPE_OFF, "OFF", __FILE__, __LINE__, __FUNCTION__
#define eGINF   LOG_TYPE_INF, "INF", __FILE__, __LINE__, __FUNCTION__
#define eGERR   LOG_TYPE_ERR, "ERR", __FILE__, __LINE__, __FUNCTION__
//===============================================
class GLog {
public:
    GLog();
    ~GLog();
    void operator()(int _level, const char* _name, const char* _file, int _line, const char* _func, const char* _format, ...) const;

private:
    std::string getDate(const std::string& _format) const;
    std::string getFormat(const char* _format, ...) const;
};
//===============================================
