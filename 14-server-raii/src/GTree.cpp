//===============================================
#include "GTree.h"
#include "GTemplate.h"
//===============================================
GTree::GTree() {

}
//===============================================
GTree::~GTree() {

}
//===============================================
void GTree::run() {
    GTemplate lTemplate;
    m_responseData = lTemplate.parse("/private/test/template/tree.html");
    m_errors.addErrors(lTemplate.getErrors());
}
//===============================================
