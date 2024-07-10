//===============================================
#pragma once
//===============================================
#include "GObject.h"
//===============================================
class GTreeData : public GObject {
public:
    GTreeData(int _index, int _parentIndex, const GString& _name, const GString& _type);
    ~GTreeData();
    GString serializeJson() const;
    void deserializeJson(const GString& _data);

public:
    int getIndex() const            {return m_index;}
    int getParentIndex() const      {return m_parentIndex;}
    const GString& getName() const  {return m_name;}
    const GString& geType() const   {return m_type;}

private:
    int m_index;
    int m_parentIndex;
    GString m_name;
    GString m_type;
};
//===============================================
