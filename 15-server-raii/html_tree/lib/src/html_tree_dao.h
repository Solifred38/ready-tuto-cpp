#pragma once

#include "html_tree_header.h"

class html_tree_data;

class html_tree_dao : public common_object {
public:
    html_tree_dao();
    ~html_tree_dao();
    void saveTree(const std::vector<html_tree_data>& _treeMap);
    void saveTree(const html_tree_data& _treeData);

private:
    common_string m_dbRoot;
    common_string m_dbPath;
};
