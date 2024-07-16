#include "html_tree_dao.h"
#include "html_tree_data.h"
#include "db_sqlite.h"

html_tree_dao::html_tree_dao()
: m_dbRoot  ("../../../maj_db_sqlite/res")
, m_dbPath  ("/private/database/sqlite/db/test.dat") {

}

html_tree_dao::~html_tree_dao() {

}

void html_tree_dao::saveTree(const std::vector<html_tree_data>& _treeMap) {
     std::vector<html_tree_data>::const_iterator it;
    for(it = _treeMap.begin(); it != _treeMap.end(); ++it) {
        html_tree_data lTreeData = *it;
        saveTree(lTreeData);
        if(m_errors.hasErrors()) break;
    }
}

void html_tree_dao::saveTree(const html_tree_data& _treeData) {
    db_sqlite dbSQL(m_dbRoot, m_dbPath);

    dbSQL.bindInt(1, _treeData.getIndex());
    dbSQL.bindInt(2, _treeData.getParentIndex());
    dbSQL.bindText(3, _treeData.getName());
    dbSQL.bindText(4, _treeData.getType());

    dbSQL.insertQuery(""
    "insert into _html_tree (_index, _parent_index, _name, _file) "
    "values (?, ?, ?, ?)"
    "");

    m_errors.addErrors(dbSQL.getErrors());
}

