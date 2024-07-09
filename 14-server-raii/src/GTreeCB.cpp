//===============================================
#include "GTreeCB.h"
#include "GTemplate.h"
//===============================================
GTreeCB::GTreeCB() {

}
//===============================================
GTreeCB::~GTreeCB() {

}
//===============================================
void GTreeCB::run() {
    GTemplate lTemplate;
    m_responseData = lTemplate.parse("/private/test/template/tree.html");
}
//===============================================
