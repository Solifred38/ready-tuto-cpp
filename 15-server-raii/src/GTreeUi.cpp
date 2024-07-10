//===============================================
#include "GTreeUi.h"
#include "GTemplate.h"
//===============================================
GTreeUi::GTreeUi() {

}
//===============================================
GTreeUi::~GTreeUi() {

}
//===============================================
void GTreeUi::run() {
    GTemplate lTemplate;
    m_responseData = lTemplate.parse("/private/test/template/tree.html");
    m_errors.addErrors(lTemplate.getErrors());
}
//===============================================
