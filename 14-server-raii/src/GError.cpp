//===============================================
#include "GError.h"
//===============================================
GError::GError() {

}
//===============================================
GError::~GError() {

}
//===============================================
void GError::addError(const GString& _error) {
    m_errors.push_back(_error);
}
//===============================================
void GError::addErrors(const GError& _obj) {
    for(int i = 0; i < _obj.size(); i++) {
        GString lError = _obj.at(i);
        m_errors.push_back(lError);
    }
}
//===============================================
void GError::addProblem() {
    addError("Un problème a été rencontré.");
}
//===============================================
GString GError::toString() const {
    GString lErrors;
    for(int i = 0; i < m_errors.size(); i++) {
        lErrors += m_errors.at(i) + "\n";
    }
    return lErrors;
}
//===============================================
