//===============================================
#pragma once
//===============================================
#include "GInclude.h"
//===============================================
class GString : public std::string {
public:
    GString();
    GString(const char* _data);
    GString(const std::string& _data);
    ~GString();
    int countMatch(const GString& _match) const;
    GString searchMatch(const GString& _search, int _capture, int _pos) const;
    bool isMatch(const GString& _match) const;
    GString replaceMatch(const GString& _from, const GString& _to) const;
    GString replaceAll(const GString& _from, const GString& _to) const;
};
//===============================================
