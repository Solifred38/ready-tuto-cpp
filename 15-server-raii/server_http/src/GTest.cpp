//===============================================
#include "GTest.h"
//===============================================
GTest::GTest(const GModule& _module)
: m_module  (_module) {

}
//===============================================
GTest::~GTest() {

}
//===============================================
void GTest::run() {
    if(m_module.getMethod() == "test") {
        runTest();
    }
    else {
        slog(eGERR, "La méthode est inconnue."
        "|module=%s"
        "|method=%s"
        "|params=%s", m_module.getModule().c_str(), m_module.getMethod().c_str(), m_module.getParams().c_str());
    }
}
//===============================================
void GTest::runTest() {
    slog(eGINF, "L'exécution du test a démarré."
    "|module=%s"
    "|method=%s"
    "|params=%s", m_module.getModule().c_str(), m_module.getMethod().c_str(), m_module.getParams().c_str());
}
//===============================================
