#include "common_string.h"

common_string* common_string::m_instance = 0;

common_string::common_string() {

}

common_string::common_string(int _data) {
    int lSize = snprintf(0, 0, "%d", _data);
    char* lData = new char[lSize + 1];
    snprintf(lData, lSize + 1, "%d", _data);
    std::string lString(lData, lSize);
    *this = lString;
    delete[] lData;
}

common_string::common_string(const char* _data)
: std::string(_data) {

}

common_string::common_string(char* _data, int _size)
: std::string(_data, _size) {

}

common_string::common_string(const std::string& _data)
: std::string(_data) {

}

common_string::common_string(const std::vector<char>& _data)
: std::string(_data.begin(), _data.end()) {

}

common_string::common_string(const std::vector<uchar>& _data)
: std::string(_data.begin(), _data.end()) {

}

common_string::~common_string() {

}

common_string* common_string::Instance() {
    if(m_instance == 0) {
        m_instance = new common_string;
    }
    return m_instance;
}

common_string common_string::getFormat(const char* _format, ...) const {
    va_list lArgs;
    va_start(lArgs, _format);
    int lSize = vsnprintf(0, 0, _format, lArgs);
    char* lData = new char[lSize + 1];
    vsnprintf(lData, lSize + 1, _format, lArgs);
    va_end(lArgs);
    common_string lString(lData, lSize);
    delete[] lData;
    return lString;
}

bool common_string::startsWith(const common_string& _data) const {
    if(empty()) return false;
    if(size() < _data.size()) return false;
    return (substr(0, _data.size()) == _data);
}

bool common_string::endsWith(const common_string& _data) const {
    if(empty()) return false;
    if(size() < _data.size()) return false;
    return (substr(size() - _data.size(), _data.size()) == _data);
}

int common_string::indexOf(const common_string& _data, int _pos) const {
    return find(_data, _pos);
}

int common_string::countSep(const common_string& _sep) const {
    int lPos = 0;
    int lCount = 1;
    while(1) {
        lPos = indexOf(_sep, lPos);
        if(lPos == std::string::npos) {
            break;
        }
        lPos += _sep.size();
        lCount++;
    }
    return lCount;
}

common_string common_string::extractSep(const common_string& _sep, int _index) const {
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

common_string common_string::extractSeps(const common_string& _sep1, const common_string& _sep2, int _pos) {
    int lPos1 = indexOf(_sep1, _pos);
    if(lPos1 == std::string::npos) return "";
    int lPos2 = lPos1 + _sep1.size();
    int lPos3 = indexOf(_sep2, lPos2);
    if(lPos3 == std::string::npos) return "";
    int lSize = lPos3 - lPos2;
    return substr(lPos2, lSize);
}

common_string common_string::extractEnd(const common_string& _sep, int _index) const {
    int lPos = 0;
    int lCount = 0;
    while(1) {
        int lPos2 = indexOf(_sep, lPos);
        if(lPos2 == -1) {
            int lSize = size() - lPos;
            return substr(lPos, lSize);
        }
        if(lCount == _index) {
            lPos = lPos2 + _sep.size();
            return substr(lPos);
        }
        lPos = lPos2 + _sep.size();
        lCount++;
    }
    return "";
}

common_string common_string::limit(int _max) const {
    if(_max >= size()) return *this;
    return substr(0, _max) + "...";
}

common_string common_string::getFilepath() const {
    size_t lFound = find_last_of("/\\");
    if(lFound == std::string::npos) return *this;
    return substr(0, lFound);
}

common_string common_string::getFilename() const {
    size_t lFound = find_last_of("/\\");
    if(lFound == std::string::npos) return *this;
    return substr(lFound + 1);
}

common_string common_string::getBasename() const {
    common_string lFilename = getFilename();
    size_t lFound = lFilename.find_last_of(".");
    if(lFound == std::string::npos) return *this;
    return lFilename.substr(0, lFound);
}

common_string common_string::getExtension() const {
    common_string lFilename = getFilename();
    size_t lFound = lFilename.find_last_of(".");
    if(lFound == std::string::npos) return "";
    return lFilename.substr(lFound + 1);
}

common_string common_string::toUpper() const {
    std::string lData = *this;
    std::transform(lData.begin(), lData.end(), lData.begin(), ::toupper);
    return lData;
}

common_string common_string::toLower() const {
    std::string lData = *this;
    std::transform(lData.begin(), lData.end(), lData.begin(), ::tolower);
    return lData;
}

int common_string::toInt() const {
    int lData = 0;
    try {
        lData = std::stoi(*this);
    }
    catch(const std::exception& e) {
        lData = 0;
    }
    return lData;
}

int common_string::countMatch(const common_string& _match) const {
    if(empty()) return 0;
    try {
        common_string lData = *this;
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

common_string common_string::searchMatch(const common_string& _search, int _capture, int _pos) const {
    if(empty()) return 0;
    try {
        std::smatch sm1;
        common_string lData = *this;
        std::regex lRegex(_search.c_str());
        int lCapture = 0;
        int lPos = 0;
        while(std::regex_search(lData, sm1, lRegex)) {
            if(lCapture++ == _capture) {
                for(auto x : sm1) {
                    if(lPos++ == _pos) {
                        return common_string(x);
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

common_string common_string::replaceMatch(const common_string& _from, const common_string& _to) const {
    if(empty()) return "";
    try {
        std::regex reg(_from.c_str());
        common_string lData = std::regex_replace(*this, reg, _to.c_str());
        return lData;
    }
    catch(std::regex_error e) {
        std::cout << "L'exécution de l'expression regulière a échoué."
        "|codeErreur=" << e.code() <<
        "|msgErreur=" << e.what() << std::endl;
    }
    return "";
}

bool common_string::isMatch(const common_string& _match) const {
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

common_string common_string::replaceAll(const common_string& _from, const common_string& _to) const {
    if(empty()) return "";
    common_string lData = *this;
    size_t start_pos = 0;
    while((start_pos = lData.find(_from.c_str(), start_pos)) != common_string::npos) {
        lData.replace(start_pos, _from.size(), _to.c_str());
        start_pos += _to.size();
    }
    return lData;
}

common_string common_string::trim() const {
    return ltrim().rtrim();
}

common_string common_string::ltrim() const {
    common_string lData = *this;
    lData.erase(lData.begin(), std::find_if(lData.begin(), lData.end(), [](unsigned char ch) {
        return !std::isspace(ch);
    }));
    return lData;
}

common_string common_string::rtrim() const {
    common_string lData = *this;
    lData.erase(std::find_if(lData.rbegin(), lData.rend(), [](unsigned char ch) {
        return !std::isspace(ch);
    }).base(), lData.end());
    return lData;
}

void common_string::print() const {
    std::cout << *this << std::endl;
}

