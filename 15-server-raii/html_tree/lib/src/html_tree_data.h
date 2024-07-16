#pragma once

#include "html_tree_header.h"

class html_tree_data : public common_object {
public:
    html_tree_data(int _index, int _parentIndex, const common_string& _name, const common_string& _type);
    ~html_tree_data();
    common_string serializeJson() const;
    void deserializeJson(const common_string& _data);

public:
    int getIndex() const            {return m_index;}
    int getParentIndex() const      {return m_parentIndex;}
    const common_string& getName() const  {return m_name;}
    const common_string& getType() const   {return m_type;}

private:
    int m_index;
    int m_parentIndex;
    common_string m_name;
    common_string m_type;
};

