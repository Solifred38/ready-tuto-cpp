//===============================================
#include "GInclude.h"
//===============================================
std::map<int, std::string> GMAP_DATA = {
    {0, "zero"},
    {1, "Un"},
    {2, "Deux"},
    {3, "Trois"}
};
//===============================================
std::string GMAP_GET_VALUE(int _key) {
    std::string lValue;
    std::map<int, std::string>::iterator it = std::find_if(GMAP_DATA.begin()
    , GMAP_DATA.end(), [&](const std::pair<int, std::string>& _pair) {
        return _pair.first == _key;
    });
    if(it != GMAP_DATA.end()) {
        lValue = it->second;
    };
    return lValue;
}
//===============================================
int GMAP_GET_KEY(std::string _value) {
    int lKey;
    std::map<int, std::string>::iterator it = std::find_if(GMAP_DATA.begin()
    , GMAP_DATA.end(), [&](const std::pair<int, std::string>& _pair) {
        return _pair.second == _value;
    });
    if(it != GMAP_DATA.end()) {
        lKey = it->first;
    };
    return lKey;
}
//===============================================
bool GMAP_EXIST_VALUE(int _key) {
    std::map<int, std::string>::iterator it = std::find_if(GMAP_DATA.begin()
    , GMAP_DATA.end(), [&](const std::pair<int, std::string>& _pair) {
        return _pair.first == _key;
    });
    return (it != GMAP_DATA.end());
}
//===============================================
bool GMAP_EXIST_KEY(std::string _value) {
    std::map<int, std::string>::iterator it = std::find_if(GMAP_DATA.begin()
    , GMAP_DATA.end(), [&](const std::pair<int, std::string>& _pair) {
        return _pair.second == _value;
    });
    return (it != GMAP_DATA.end());
}
//===============================================
int main(int _argc, char** _argv) {
    std::cout << "GMAP_GET_VALUE : " << GMAP_GET_VALUE(0) << std::endl;
    std::cout << "GMAP_GET_KEY : " << GMAP_GET_KEY("Un") << std::endl;
    std::cout << "GMAP_GET_VALUE : " << GMAP_GET_VALUE(5) << std::endl;
    std::cout << "GMAP_GET_KEY : " << GMAP_GET_KEY("Cinq") << std::endl;
    std::cout << "GMAP_GET_VALUE : " << GMAP_EXIST_VALUE(0) << std::endl;
    std::cout << "GMAP_EXIST_KEY : " << GMAP_EXIST_KEY("Un") << std::endl;
    std::cout << "GMAP_EXIST_VALUE : " << GMAP_EXIST_VALUE(5) << std::endl;
    std::cout << "GMAP_EXIST_KEY : " << GMAP_EXIST_KEY("Cinq") << std::endl;
    return 0;
}
//===============================================
