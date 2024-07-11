#pragma once

#include "common_string.h"

class common_error {
public:
    common_error();
    ~common_error();
    void addError(const common_string& _error);
    void addErrors(const common_error& _obj);
    void addProblem();
    common_string toString() const;

public:
    bool hasErrors() const                  {return !m_errors.empty();}
    common_string at(int i) const    {return m_errors.at(i);}
    int size() const                        {return m_errors.size();}

private:
    std::vector<common_string> m_errors;
};

