//===============================================
#pragma once
//===============================================
#include "GInclude.h"
//===============================================
class GString : public std::string {
public:
    GString();
    GString(const char* _data);
    GString(char* _data, int _size);
    GString(const std::string& _data);
    ~GString();
    bool startsWith(const GString& _data) const;
    bool endsWith(const GString& _data) const;
    int indexOf(const GString& _data, int _pos = 0) const;
    GString extractSep(const GString& _sep, int _index = 0) const;
    GString extractSeps(const GString& _sep1, const GString& _sep2, int _pos = 0);
};
//===============================================
