#pragma once

#include "server_http_header.h"
#include "server_http_response_http_status.h"

class server_http_object : public common_object {
public:
    server_http_object();
    ~server_http_object();

public:
    const e_server_http_response_http_status& getResponseStatus() const     {return m_responseStatus;}
    const common_string& getResponseType() const                            {return m_responseType;}
    const common_string& getResponseText() const                            {return m_responseText;}
    const common_string& getResponseData() const                            {return m_responseData;}

protected:
    e_server_http_response_http_status m_responseStatus;
    common_string m_responseType;
    common_string m_responseData;
    common_string m_responseText;
};
