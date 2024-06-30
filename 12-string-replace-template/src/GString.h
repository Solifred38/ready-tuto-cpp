//===============================================
#pragma once
//===============================================
#include "GInclude.h"
//===============================================
#define GSTRINGI    GString::Instance()
#define sformat     GSTRINGI->getFormat
//===============================================
class GString : public std::string {
public:
    GString();
    GString(int _data);
    GString(const char* _data);
    GString(char* _data, int _size);
    GString(const std::string& _data);
    GString(const std::vector<char>& _data);
    GString(const std::vector<uchar>& _data);
    ~GString();
    static GString* Instance();
    GString getFormat(const char* _format, ...) const;
    bool startsWith(const GString& _data) const;
    bool endsWith(const GString& _data) const;
    int indexOf(const GString& _data, int _pos = 0) const;
    GString extractSep(const GString& _sep, int _index = 0) const;
    GString extractSeps(const GString& _sep1, const GString& _sep2, int _pos = 0);
    GString limit(int _max = rdv::STRING_LIMIT_DEFAULT) const;
    GString getFilepath() const;
    GString getFilename() const;
    GString getBasename() const;
    GString getExtension() const;
    GString toUpper() const;
    GString toLower() const;
    int countMatch(const GString& _match) const;
    GString searchMatch(const GString& _search, int _capture, int _pos) const;
    bool isMatch(const GString& _match) const;
    GString replaceMatch(const GString& _from, const GString& _to) const;
    GString replaceAll(const GString& _from, const GString& _to) const;

private:
    static GString* m_instance;
};
//===============================================
