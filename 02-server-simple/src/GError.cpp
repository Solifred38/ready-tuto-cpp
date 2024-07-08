//===============================================
#include "GError.h"
//===============================================
GError::GError() {

}
//===============================================
GError::~GError() {

}
//===============================================
void GError::addError(const std::string& _error) {
    m_errors.push_back(_error);
}
//===============================================
void GError::addErrors(const GError& _obj) {
    for(int i = 0; i < _obj.size(); i++) {
        std::string lError = _obj.at(i);
        m_errors.push_back(lError);
    }
}
//===============================================
void GError::addProblem() {
    addError("Un problème a été rencontré.");
}
//===============================================
void GError::showErrors() {
    for(int i = 0; i < m_errors.size(); i++) {
        std::string lError = m_errors.at(i);
        std::cout << lError << std::endl;
    }
}
//===============================================
