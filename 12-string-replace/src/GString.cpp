//===============================================
#include "GString.h"
//===============================================
GString::GString() {

}
//===============================================
GString::GString(const char* _data)
: std::string(_data) {

}
//===============================================
GString::GString(const std::string& _data)
: std::string(_data) {

}
//===============================================
GString::~GString() {

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
