//===============================================
#pragma once
//===============================================
#include "GObject.h"
//===============================================
class GTreeData;
//===============================================
class GTreeDao : public GObject {
public:
    GTreeDao();
    ~GTreeDao();
    void saveTree(const std::vector<GTreeData>& _treeMap);
    void saveTree(const GTreeData& _treeData);
};
//===============================================
