//===============================================
#include "GTreeData.h"
//===============================================
GTreeData::GTreeData(int _index, int _parentIndex, const GString& _name, const GString& _type)
: m_index       (_index)
, m_parentIndex (_parentIndex)
, m_name        (_name)
, m_type        (_type) {

}
//===============================================
GTreeData::~GTreeData() {

}
//===============================================
GString GTreeData::serializeJson() const {
    nlohmann::json lJson;
    lJson["index"]          = m_index;
    lJson["parentIndex"]    = m_parentIndex;
    lJson["name"]           = m_name;
    lJson["type"]           = m_type;
    return lJson.dump();
}
//===============================================
void GTreeData::deserializeJson(const GString& _data) {
    nlohmann::json lJson = nlohmann::json::parse(_data.c_str());
    m_index         = lJson["index"];
    m_parentIndex   = lJson["parent_index"];
    m_name          = lJson["name"];
    m_type          = lJson["type"];
}
//===============================================
