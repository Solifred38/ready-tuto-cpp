//===============================================
#include "GTreeDao.h"
#include "GTreeData.h"
#include "GSQLite.h"
//===============================================
GTreeDao::GTreeDao() {

}
//===============================================
GTreeDao::~GTreeDao() {

}
//===============================================
void GTreeDao::saveTree(const std::vector<GTreeData>& _treeMap) {
     std::vector<GTreeData>::const_iterator it;
    for(it = _treeMap.begin(); it != _treeMap.end(); ++it) {
        GTreeData lTreeData = *it;
        saveTree(lTreeData);
    }
}
//===============================================
void GTreeDao::saveTree(const GTreeData& _treeData) {
    GString lRequest = ""
    "create table test ("
    "id integer primary key,"
    "foo real,"
    "bar text"
    ")";

    GSQLite dbSQL;
    dbSQL.execQuery(lRequest);
    m_errors.addErrors(dbSQL.getErrors());
}
//===============================================
