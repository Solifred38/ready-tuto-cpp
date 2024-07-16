#pragma once

#include "common_object.h"

class common_resource : public common_object {
public:
    common_resource(const common_string& _filename);
    ~common_resource();
    void run();

public:
    const common_string& getResponseType()  {return m_responseType;}
    const common_string& getResponseData()  {return m_responseData;}

private:
    common_string m_resourceRoot;
    common_string m_filename;
    common_string m_responseType;
    common_string m_responseData;
};
