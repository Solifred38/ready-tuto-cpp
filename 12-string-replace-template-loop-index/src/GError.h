//===============================================
#pragma once
//===============================================
#include "GInclude.h"
//===============================================
class GError {
public:
    GError();
    ~GError();
    void addError(const std::string& _error);
    void addErrors(const GError& _obj);
    void addProblem();
    void showErrors();

public:
    bool hasErrors() const          {return !m_errors.empty();}
    std::string at(int i) const     {return m_errors.at(i);}
    int size() const                {return m_errors.size();}

private:
    std::vector<std::string> m_errors;
};
//===============================================
