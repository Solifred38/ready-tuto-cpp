//===============================================
#include "GInclude.h"
//===============================================
#define GENUM_DEFINE(eGEnum, ...) \
enum class eGEnum { \
    __VA_ARGS__ \
};
//===============================================
#define GENUM_CONVERT(eGEnum, eGType) \
std::map<eGEnum, eGType> GEnum_##eGEnum##_Map = { \
      {eGEnum::RED, "Red"} \
    , {eGEnum::GREEN, "Green"} \
    , {eGEnum::BLUE, "Blue"} \
}; \
\
eGType GEnum_##eGEnum##_To_String(eGColor eGVar) { \
    return GEnum_##eGEnum##_Map[eGVar]; \
} \
\
eGEnum GEnum_##eGEnum##_From_String(eGType _data) { \
    eGEnum lEnum; \
    std::map<eGEnum, eGType>::iterator it = std::find_if(GEnum_##eGEnum##_Map.begin() \
    , GEnum_##eGEnum##_Map.end(), [&](const std::pair<eGEnum, eGType>& _pair) { \
        return _pair.second == _data; \
    }); \
    if(it != GEnum_##eGEnum##_Map.end()) { \
        lEnum = it->first; \
    }; \
    return lEnum; \
}
//===============================================
GENUM_DEFINE(
    eGColor
    , RED
    , GREEN
    , BLUE
)
//===============================================
GENUM_CONVERT(eGColor, std::string)
//===============================================
int main(int _argc, char** _argv) {
    std::cout << "Enum_To_String: " << GEnum_eGColor_To_String(eGColor::GREEN) << std::endl;
    std::cout << "Enum_From_String: " << GEnum_eGColor_To_String(GEnum_eGColor_From_String("Green")) << std::endl;
    return 0;
}
//===============================================
