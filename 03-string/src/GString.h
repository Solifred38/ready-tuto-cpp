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
};
//===============================================
