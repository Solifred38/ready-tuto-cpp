//===============================================
#include "GTemplate.h"
#include "GFile.h"
//===============================================
GTemplate::GTemplate()
: m_templateRoot("../web") {

}
//===============================================
GTemplate::GTemplate(const GString& _filename)
: m_templateRoot    ("../web")
, m_filename        (_filename) {

}
//===============================================
GTemplate::~GTemplate() {

}
//===============================================
GString GTemplate::getData() {
    GString lPath = m_templateRoot + m_filename;
    GFile lFile(lPath);
    GString lData = lFile.readBin();
    m_errors.addErrors(lFile.getErrors());
    return lData;
}
//===============================================
