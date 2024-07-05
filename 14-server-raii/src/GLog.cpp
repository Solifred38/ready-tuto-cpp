//===============================================
#include "GLog.h"
//===============================================
GLog::GLog() {

}
//===============================================
GLog::~GLog() {

}
//===============================================
void GLog::operator()(int _level, const char* _name, const char* _file, int _line, const char* _func, const char* _format, ...) const {
    if(_level == LOG_TYPE_OFF) return;
    va_list lArgs;
    va_start(lArgs, _format);
    int lSize = vsnprintf(0, 0, _format, lArgs);
    char* lBuffer = new char[lSize + 1];
    vsnprintf(lBuffer, lSize + 1, _format, lArgs);
    va_end(lArgs);
    GString lData(lBuffer, lSize);
    delete[] lBuffer;
    GString lDate = getDate("%d/%m/%Y %H:%M:%S");
    GString lLogs = getFormat("%s|%s:%d|%s|%s|%s", lDate.c_str(), _file, _line, _func, _name, lData.c_str());
    std::cout << lLogs << std::endl;
}
//===============================================
GString GLog::getDate(const GString& _format) const {
    time_t lTime;
    struct tm* lTimeInfo;
    char lBuffer[80];
    time(&lTime);
    lTimeInfo = localtime(&lTime);
    strftime(lBuffer, sizeof(lBuffer), _format.c_str(), lTimeInfo);
    return lBuffer;
}
//===============================================
GString GLog::getFormat(const char* _format, ...) const {
    va_list lArgs;
    va_start(lArgs, _format);
    int lSize = vsnprintf(0, 0, _format, lArgs);
    char* lData = new char[lSize + 1];
    vsnprintf(lData, lSize + 1, _format, lArgs);
    va_end(lArgs);
    GString lString(lData, lSize);
    delete[] lData;
    return lString;
}
//===============================================
