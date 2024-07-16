#pragma once

#include "common_object.h"

class common_template : public common_object {
public:
    common_template(const common_string& _templateRoot);
    common_template();
    ~common_template();
    common_string parse(const common_string& _filename);
    common_string render(const common_string& _data);

public:
    common_template& operator=(const common_template& _obj);
    nlohmann::json& operator[](const common_string& _key);

private:
    common_string m_templateRoot;
    nlohmann::json m_dataJson;
};

