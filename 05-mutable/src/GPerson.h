//===============================================
#pragma once
//===============================================
#include "GInclude.h"
//===============================================
class GPerson {
public:
    GPerson();
    ~GPerson();
    std::string getName() const;
    std::string getCode() const;

private:
    std::string m_name;
    mutable std::string m_code;
};
//===============================================
