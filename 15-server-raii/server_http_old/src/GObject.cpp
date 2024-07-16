//===============================================
#include "GObject.h"
//===============================================
GObject::GObject()
: m_responseType    (rdv::RESPONSE_TYPE_HTML)
, m_responseStatus  (eGResponseHttpStatus::Ok) {

}
//===============================================
GObject::~GObject() {

}
//===============================================
