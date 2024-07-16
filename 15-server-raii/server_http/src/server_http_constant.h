
#pragma once

#include <string>

namespace rdv {
// http
const std::string HTTP_1_1                      = "HTTP/1.1";
const std::string HTTP_REQUEST_GET              = "GET";
const std::string HTTP_REQUEST_POST             = "POST";

// request
const std::string REQUEST_TYPE_FORM             = "application/x-www-form-urlencoded";
const std::string REQUEST_TYPE_JSON             = "application/json";

// response
const std::string RESPONSE_TYPE_HTML            = "text/html; charset=UTF-8";
const std::string RESPONSE_TYPE_JSON            = "application/json; charset=UTF-8";

// socket
const int SOCKET_BUFFER_MAX                     = 1*1024*1024; // 1Mo

// string
const int STRING_LIMIT_DEFAULT                  = 1024;
}
