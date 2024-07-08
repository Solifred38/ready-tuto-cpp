//===============================================
#pragma once
//===============================================
#include "GString.h"
//===============================================
class GError {
public:
    GError();
    ~GError();
    void addError(const GString& _error);
    void addErrors(const GError& _obj);
    void addProblem();
    GString toString() const;

public:
    bool hasErrors() const          {return !m_errors.empty();}
    GString at(int i) const         {return m_errors.at(i);}
    int size() const                {return m_errors.size();}

private:
    std::vector<GString> m_errors;
};
//===============================================
