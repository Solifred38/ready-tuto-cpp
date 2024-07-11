//===============================================
#pragma once
//===============================================
#include "GObject.h"
//===============================================
class GResponseHttp : public GObject {
public:
    GResponseHttp(const GString& _responseData, const GString& _responseType, const eGResponseHttpStatus& _responseStatus);
    ~GResponseHttp();
    void run();
};
//===============================================
