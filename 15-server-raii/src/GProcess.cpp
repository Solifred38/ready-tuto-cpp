//===============================================
#include "GProcess.h"
#include "GProcessWin.h"
#include "GModule.h"
//===============================================
GProcess::GProcess(int _argc, char** _argv)
: m_argc(_argc)
, m_argv(_argv) {

}
//===============================================
GProcess::~GProcess() {

}
//===============================================
std::shared_ptr<GProcess> GProcess::create(int _argc, char** _argv) {
#if defined(_WIN32)
    return std::shared_ptr<GProcess>(new GProcessWin(_argc, _argv));
#endif
    return std::shared_ptr<GProcess>(new GProcess(_argc, _argv));
}
//===============================================
void GProcess::run() {
    initProcess();

    GString lModule;
    GString lMethod;
    GString lParams;

    if(m_argc > 1) {
        lModule = m_argv[1];
    }
    if(m_argc > 2) {
        lMethod = m_argv[2];
    }
    if(m_argc > 3) {
        lParams = m_argv[3];
    }

    GModule lModuleObj(lModule, lMethod, lParams);
    lModuleObj.run();
}
//===============================================
void GProcess::initProcess() {}
//===============================================
