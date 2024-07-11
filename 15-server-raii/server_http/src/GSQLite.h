//===============================================
#pragma once
//===============================================
#include "GObject.h"
//===============================================
GENUM_DEFINE_CLASS(
    eGSQLiteParam
    , DATA_NULL
    , DATA_INT
    , DATA_DOUBLE
    , DATA_TEXT
    , DATA_BINARY
)
//===============================================
struct sGSQLiteParam {
    eGSQLiteParam m_type;
    int m_index;
    int m_dataInt;
    double m_dataDouble;
    GString m_dataText;
};
//===============================================
class GSQLite : public GObject {
public:
    GSQLite();
    GSQLite(const GString& _filename);
    ~GSQLite();
    void execQuery(const GString& _sql);
    void prepareQuery(const GString& _sql);
    void bindNull(int _index);
    void bindInt(int _index, int _data);
    void bindDouble(int _index, double _data);
    void bindText(int _index, const GString& _data);
    void bindBinary(int _index, const GString& _data);

private:
    GString m_dbRoot;
    GString m_filename;
    std::vector<sGSQLiteParam> m_params;
};
//===============================================
