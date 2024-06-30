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
    GTemplate lTemplate("/private/test/template/home.html");
    m_responseData = lTemplate.getData();
}
//===============================================
