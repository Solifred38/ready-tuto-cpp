//===============================================
#include "GHome.h"
#include "GTemplate.h"
//===============================================
GHome::GHome() {

}
//===============================================
GHome::~GHome() {

}
//===============================================
void GHome::run() {
    GTemplate lTemplate;
    m_responseData = lTemplate.parse("/private/test/template/home.html");
}
//===============================================
