#include "common_error.h"

common_error::common_error() {

}

common_error::~common_error() {

}

void common_error::addError(const common_string& _error) {
    m_errors.push_back(_error);
}

void common_error::addErrors(const common_error& _obj) {
    for(int i = 0; i < _obj.size(); i++) {
        common_string lError = _obj.at(i);
        m_errors.push_back(lError);
    }
}

void common_error::addProblem() {
    addError("Un problème a été rencontré.");
}

common_string common_error::toString() const {
    common_string lErrors;
    for(int i = 0; i < m_errors.size(); i++) {
        lErrors += m_errors.at(i) + "\n";
    }
    return lErrors;
}

