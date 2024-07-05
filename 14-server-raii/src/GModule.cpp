//===============================================
#include "GModule.h"
#include "GTest.h"
#include "GSocket.h"
//===============================================
GModule::GModule(const GString& _module, const GString& _method, const GString& _params)
: m_module  (_module)
, m_method  (_method)
, m_params  (_params) {

}
//===============================================
GModule::~GModule() {

}
//===============================================
void GModule::run() {
    if(m_module ==  "test") {
        runTest();
    }
    else if(m_module ==  "server") {
        runServer();
    }
    else {
        slog(eGERR, "Le module est inconnu."
        "|module=%s"
        "|method=%s"
        "|params=%s", m_module.c_str(), m_method.c_str(), m_params.c_str());
    }
}
//===============================================
void GModule::runTest() {
    GTest lTest(*this);
    lTest.run();
}
//===============================================
void GModule::runServer() {
    std::shared_ptr<GSocket> lServer = GSocket::create(8080);
    lServer->run();
}
//===============================================
