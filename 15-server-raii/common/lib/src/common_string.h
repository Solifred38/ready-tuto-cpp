#pragma once

#include "common_header.h"

#define common_stringI   common_string::Instance()
#define sformat                 common_stringI->getFormat

class common_string : public std::string {
public:
    common_string();
    common_string(int _data);
    common_string(const char* _data);
    common_string(char* _data, int _size);
    common_string(const std::string& _data);
    common_string(const std::vector<char>& _data);
    common_string(const std::vector<uchar>& _data);
    ~common_string();
    static common_string* Instance();
    common_string getFormat(const char* _format, ...) const;
    bool startsWith(const common_string& _data) const;
    bool endsWith(const common_string& _data) const;
    int indexOf(const common_string& _data, int _pos = 0) const;
    int countSep(const common_string& _sep) const;
    common_string extractSep(const common_string& _sep, int _index = 0) const;
    common_string extractSeps(const common_string& _sep1, const common_string& _sep2, int _pos = 0);
    common_string extractEnd(const common_string& _sep, int _index) const;
    common_string limit(int _max) const;
    common_string getFilepath() const;
    common_string getFilename() const;
    common_string getBasename() const;
    common_string getExtension() const;
    common_string toUpper() const;
    common_string toLower() const;
    int toInt() const;
    int countMatch(const common_string& _match) const;
    common_string searchMatch(const common_string& _search, int _capture, int _pos) const;
    bool isMatch(const common_string& _match) const;
    common_string replaceMatch(const common_string& _from, const common_string& _to) const;
    common_string replaceAll(const common_string& _from, const common_string& _to) const;
    common_string trim() const;
    common_string ltrim() const;
    common_string rtrim() const;
    void print() const;

private:
    static common_string* m_instance;
};

