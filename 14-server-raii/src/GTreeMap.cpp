//===============================================
#include "GTreeMap.h"
#include "GTemplate.h"
//===============================================
GTreeMap::GTreeMap(const GString& _dataJson)
: m_dataJson(_dataJson) {

}
//===============================================
GTreeMap::~GTreeMap() {

}
//===============================================
void GTreeMap::run() {
    GTemplate lTemplate;
    m_responseData = m_dataJson;
}
//===============================================
