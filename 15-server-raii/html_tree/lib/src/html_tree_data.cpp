#include "html_tree_data.h"

html_tree_data::html_tree_data(int _index, int _parentIndex, const common_string& _name, const common_string& _type)
: m_index       (_index)
, m_parentIndex (_parentIndex)
, m_name        (_name)
, m_type        (_type) {

}

html_tree_data::~html_tree_data() {

}

common_string html_tree_data::serializeJson() const {
    nlohmann::json lJson;
    lJson["index"]          = m_index;
    lJson["parentIndex"]    = m_parentIndex;
    lJson["name"]           = m_name;
    lJson["type"]           = m_type;
    return lJson.dump();
}

void html_tree_data::deserializeJson(const common_string& _data) {
    nlohmann::json lJson = nlohmann::json::parse(_data.c_str());
    m_index         = lJson["index"];
    m_parentIndex   = lJson["parent_index"];
    m_name          = lJson["name"];
    m_type          = lJson["type"];
}

