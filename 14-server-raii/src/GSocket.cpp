//===============================================
#include "GSocket.h"
#include "GSocketWin.h"
//===============================================
GSocket::GSocket(int _port)
: m_port(_port) {

}
//===============================================
GSocket::~GSocket() {

}
//===============================================
std::shared_ptr<GSocket> GSocket::create(int _port) {
#if defined(_WIN32)
    return std::shared_ptr<GSocket>(new GSocketWin(_port));
#endif
    return 0;
}
//===============================================
