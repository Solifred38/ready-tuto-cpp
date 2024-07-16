#pragma once

#include "html_tree_header.h"

class html_tree : public common_object {
public:
    html_tree(const common_string& _dataJson);
    ~html_tree();
    void saveTree();

private:
    common_string m_dataJson;
};

