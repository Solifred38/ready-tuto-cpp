
#include "html_tree.h"
#include "html_tree_data.h"
#include "html_tree_dao.h"

html_tree::html_tree(const common_string& _dataJson)
: m_dataJson(_dataJson) {

}

html_tree::~html_tree() {

}

void html_tree::saveTree() {
    nlohmann::json lJson = nlohmann::json::parse(m_dataJson.c_str());
    nlohmann::json::iterator it;
    std::vector<html_tree_data> lTreeMap;

    for(it = lJson.begin(); it != lJson.end(); ++it) {
        nlohmann::json lDataJson = *it;

        int lIndex              = lDataJson["index"];
        int lParentIndex        = lDataJson["parent_index"];
        common_string lName     = lDataJson["name"];
        common_string lType     = lDataJson["type"];

        html_tree_data lTreeData(lIndex, lParentIndex, lName, lType);
        lTreeMap.push_back(lTreeData);
    }

    html_tree_dao dao;
    dao.saveTree(lTreeMap);
    m_errors.addErrors(dao.getErrors());
}
