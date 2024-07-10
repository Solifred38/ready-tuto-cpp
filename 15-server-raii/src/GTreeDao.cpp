//===============================================
#include "GTreeDao.h"
#include "GTreeData.h"
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
    std::cout << _treeData.serializeJson() << "\n";
}
//===============================================
