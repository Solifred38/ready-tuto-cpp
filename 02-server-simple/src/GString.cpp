//===============================================
#include "GString.h"
//===============================================
GString::GString() {

}
//===============================================
GString::GString(const char* _data)
: std::string(_data) {

}
//===============================================
GString::GString(char* _data, int _size)
: std::string(_data, _size) {

}
//===============================================
GString::GString(const std::string& _data)
: std::string(_data) {

}
//===============================================
GString::~GString() {

}
//===============================================
bool GString::startsWith(const GString& _data) const {
    if(empty()) return false;
    if(size() < _data.size()) return false;
    return (substr(0, _data.size()) == _data);
}
//===============================================
bool GString::endsWith(const GString& _data) const {
    if(empty()) return false;
    if(size() < _data.size()) return false;
    return (substr(size() - _data.size(), _data.size()) == _data);
}
//===============================================
int GString::indexOf(const GString& _data, int _pos) const {
    return find(_data, _pos);
}
//===============================================
GString GString::extractSep(const GString& _sep, int _index) const {
    int lPos = 0;
    int lCount = 0;
    while(1) {
        int lPos2 = indexOf(_sep, lPos);
        if(lPos2 == std::string::npos) {
            int lSize = size() - lPos;
            return substr(lPos, lSize);
        }
        if(lCount == _index) {
            int lSize = lPos2 - lPos;
            return substr(lPos, lSize);
        }
        lPos = lPos2 + _sep.size();
        lCount++;
    }
    return "";
}
//===============================================
GString GString::extractSeps(const GString& _sep1, const GString& _sep2, int _pos) {
    int lPos1 = indexOf(_sep1, _pos);
    if(lPos1 == std::string::npos) return "";
    int lPos2 = lPos1 + _sep1.size();
    int lPos3 = indexOf(_sep2, lPos2);
    if(lPos3 == std::string::npos) return "";
    int lSize = lPos3 - lPos2;
    return substr(lPos2, lSize);
}
//===============================================