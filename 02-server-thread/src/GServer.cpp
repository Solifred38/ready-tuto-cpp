//===============================================
#include "GServer.h"
#include "GServerWin.h"
//===============================================
GSocket::GSocket() {

}
//===============================================
GSocket::~GSocket() {

}
//===============================================
GSocket* GSocket::Create() {
#if defined(_WIN32)
    return new GSocketWin;
#endif
    return 0;
}
//===============================================
