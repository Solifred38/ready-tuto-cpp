//===============================================
#include "GString.h"
//===============================================
GString* GString::m_instance = 0;
//===============================================
GString::GString() {

}
//===============================================
GString::GString(int _data) {
    int lSize = snprintf(0, 0, "%d", _data);
    char* lData = new char[lSize + 1];
    snprintf(lData, lSize + 1, "%d", _data);
    std::string lString(lData, lSize);
    *this = lString;
    delete[] lData;
}
//===============================================
GString::GString(const char* _data)
: std::string(_data) {

}
//===============================================
GString::GString(char* _data, int _size)
: std::string(_data, _size) {

}
//===============================================
GString::GString(const std::string& _data)
: std::string(_data) {

}
//===============================================
GString::GString(const std::vector<char>& _data)
: std::string(_data.begin(), _data.end()) {

}
//===============================================
GString::GString(const std::vector<uchar>& _data)
: std::string(_data.begin(), _data.end()) {

}
//===============================================
GString::~GString() {

}
//===============================================
GString* GString::Instance() {
    if(m_instance == 0) {
        m_instance = new GString;
    }
    return m_instance;
}
//===============================================
GString GString::getFormat(const char* _format, ...) const {
    va_list lArgs;
    va_start(lArgs, _format);
    int lSize = vsnprintf(0, 0, _format, lArgs);
    char* lData = new char[lSize + 1];
    vsnprintf(lData, lSize + 1, _format, lArgs);
    va_end(lArgs);
    GString lString(lData, lSize);
    delete[] lData;
    return lString;
}
//===============================================
bool GString::startsWith(const GString& _data) const {
    if(empty()) return false;
    if(size() < _data.size()) return false;
    return (substr(0, _data.size()) == _data);
}
//===============================================
bool GString::endsWith(const GString& _data) const {
    if(empty()) return false;
    if(size() < _data.size()) return false;
    return (substr(size() - _data.size(), _data.size()) == _data);
}
//===============================================
int GString::indexOf(const GString& _data, int _pos) const {
    return find(_data, _pos);
}
//===============================================
GString GString::extractSep(const GString& _sep, int _index) const {
    int lPos = 0;
    int lCount = 0;
    while(1) {
        int lPos2 = indexOf(_sep, lPos);
        if(lPos2 == std::string::npos) {
            int lSize = size() - lPos;
            return substr(lPos, lSize);
        }
        if(lCount == _index) {
            int lSize = lPos2 - lPos;
            return substr(lPos, lSize);
        }
        lPos = lPos2 + _sep.size();
        lCount++;
    }
    return "";
}
//===============================================
GString GString::extractSeps(const GString& _sep1, const GString& _sep2, int _pos) {
    int lPos1 = indexOf(_sep1, _pos);
    if(lPos1 == std::string::npos) return "";
    int lPos2 = lPos1 + _sep1.size();
    int lPos3 = indexOf(_sep2, lPos2);
    if(lPos3 == std::string::npos) return "";
    int lSize = lPos3 - lPos2;
    return substr(lPos2, lSize);
}
//===============================================
GString GString::limit(int _max) const {
    if(_max >= size()) return *this;
    return substr(0, _max) + "...";
}
//===============================================
GString GString::getFilepath() const {
    size_t lFound = find_last_of("/\\");
    if(lFound == std::string::npos) return *this;
    return substr(0, lFound);
}
//===============================================
GString GString::getFilename() const {
    size_t lFound = find_last_of("/\\");
    if(lFound == std::string::npos) return *this;
    return substr(lFound + 1);
}
//===============================================
GString GString::getBasename() const {
    GString lFilename = getFilename();
    size_t lFound = lFilename.find_last_of(".");
    if(lFound == std::string::npos) return *this;
    return lFilename.substr(0, lFound);
}
//===============================================
GString GString::getExtension() const {
    GString lFilename = getFilename();
    size_t lFound = lFilename.find_last_of(".");
    if(lFound == std::string::npos) return "";
    return lFilename.substr(lFound + 1);
}
//===============================================
GString GString::toUpper() const {
    std::string lData = *this;
    std::transform(lData.begin(), lData.end(), lData.begin(), ::toupper);
    return lData;
}
//===============================================
GString GString::toLower() const {
    std::string lData = *this;
    std::transform(lData.begin(), lData.end(), lData.begin(), ::tolower);
    return lData;
}
//===============================================
int GString::countMatch(const GString& _match) const {
    if(empty()) return 0;
    try {
        GString lData = *this;
        std::regex words_regex(_match.c_str());
        auto words_begin = std::sregex_iterator(lData.begin(), lData.end(), words_regex);
        auto words_end = std::sregex_iterator();

        return std::distance(words_begin, words_end);
    }
    catch(std::regex_error e) {
        std::cout << "L'exécution de l'expression regulière a échoué."
        "|codeErreur=" << e.code() <<
        "|msgErreur=" << e.what() << std::endl;
    }
    return 0;
}
//===============================================
GString GString::searchMatch(const GString& _search, int _capture, int _pos) const {
    if(empty()) return 0;
    try {
        std::smatch sm1;
        GString lData = *this;
        std::regex lRegex(_search.c_str());
        int lCapture = 0;
        int lPos = 0;
        while(std::regex_search(lData, sm1, lRegex)) {
            if(lCapture++ == _capture) {
                for(auto x : sm1) {
                    if(lPos++ == _pos) {
                        return GString(x);
                    }
                }
            }
            lData = sm1.suffix().str();
        }
    }
    catch(std::regex_error e) {
        std::cout << "L'exécution de l'expression regulière a échoué."
        "|codeErreur=" << e.code() <<
        "|msgErreur=" << e.what() << std::endl;
    }
    return "";
}
//===============================================
GString GString::replaceMatch(const GString& _from, const GString& _to) const {
    if(empty()) return "";
    try {
        std::regex reg(_from.c_str());
        GString lData = std::regex_replace(*this, reg, _to.c_str());
        return lData;
    }
    catch(std::regex_error e) {
        std::cout << "L'exécution de l'expression regulière a échoué."
        "|codeErreur=" << e.code() <<
        "|msgErreur=" << e.what() << std::endl;
    }
    return "";
}
//===============================================
bool GString::isMatch(const GString& _match) const {
    if(empty()) return false;
    try {
        std::regex pattern(_match.c_str());
        return std::regex_match(*this, pattern);
    }
    catch(std::regex_error e) {
        std::cout << "L'exécution de l'expression regulière a échoué."
        "|codeErreur=" << e.code() <<
        "|msgErreur=" << e.what() << std::endl;
    }
    return false;
}
//===============================================
GString GString::replaceAll(const GString& _from, const GString& _to) const {
    if(empty()) return "";
    GString lData = *this;
    size_t start_pos = 0;
    while((start_pos = lData.find(_from.c_str(), start_pos)) != GString::npos) {
        lData.replace(start_pos, _from.size(), _to.c_str());
        start_pos += _to.size();
    }
    return lData;
}
//===============================================
