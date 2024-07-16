
#include "server_http_object.h"

server_http_object::server_http_object()
: m_responseType    (rdv::RESPONSE_TYPE_HTML)
, m_responseStatus  (e_server_http_response_http_status::Ok) {

}

server_http_object::~server_http_object() {

}
