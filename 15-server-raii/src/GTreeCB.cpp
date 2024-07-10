//===============================================
#include "GTreeCB.h"
#include "GTreeData.h"
#include "GTreeDao.h"
//===============================================
GTreeCB::GTreeCB(const GString& _dataJson)
: m_dataJson(_dataJson) {

}
//===============================================
GTreeCB::~GTreeCB() {

}
//===============================================
void GTreeCB::run() {
    nlohmann::json lJson = nlohmann::json::parse(m_dataJson.c_str());
    nlohmann::json::iterator it;
    std::vector<GTreeData> lTreeMap;

    for(it = lJson.begin(); it != lJson.end(); ++it) {
        nlohmann::json lDataJson = *it;

        int lIndex          = lDataJson["index"];
        int lParentIndex    = lDataJson["parent_index"];
        GString lName       = lDataJson["name"];
        GString lType       = lDataJson["type"];

        GTreeData lTreeData(lIndex, lParentIndex, lName, lType);
        lTreeMap.push_back(lTreeData);
    }

    GTreeDao dao;
    dao.saveTree(lTreeMap);
    m_errors.addErrors(dao.getErrors());
}
//===============================================
