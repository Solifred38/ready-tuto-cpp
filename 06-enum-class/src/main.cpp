//===============================================
#include "GInclude.h"
//===============================================
enum class eGColor {
      RED
    , GREEN
    , BLUE
};
//===============================================
std::map<eGColor, std::string> eColor_Map = {
      {eGColor::RED, "Red"}
    , {eGColor::GREEN, "Green"}
    , {eGColor::BLUE, "Blue"}
};
//===============================================
std::string eGolor_To_String(eGColor _enum) {
    return eColor_Map[_enum];
}
//===============================================
eGColor eGolor_From_String(std::string _data) {
    eGColor lEnum;
    std::map<eGColor, std::string>::iterator it = std::find_if(eColor_Map.begin()
    , eColor_Map.end(), [&](const std::pair<eGColor, std::string>& _pair) {
        return _pair.second == _data;
    });
    if(it != eColor_Map.end()) {
        lEnum = it->first;
    };
    return lEnum;
}
//===============================================
int main(int _argc, char** _argv) {
    std::cout << "Enum_To_String: " << eGolor_To_String(eGColor::GREEN) << std::endl;
    std::cout << "Enum_From_String: " << eGolor_To_String(eGolor_From_String("Green")) << std::endl;
    return 0;
}
//===============================================
