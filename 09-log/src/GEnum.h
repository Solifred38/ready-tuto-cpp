//===============================================
#pragma once
//===============================================
#define GENUM_DEFINE(eGEnum, ...) \
enum eGEnum { \
    __VA_ARGS__ \
};
//===============================================
#define GENUM_CONVERT(eGEnum, eGType, ...) \
std::map<eGEnum, eGType> GEnum_##eGEnum##_Map = { \
    __VA_ARGS__ \
}; \
\
eGType GEnum_##eGEnum##_To_Value(eGEnum eGVar) { \
    return GEnum_##eGEnum##_Map[eGVar]; \
} \
\
eGEnum GEnum_##eGEnum##_From_Value(eGType _data) { \
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
#define GENUM_TO_VALUE(eGEnum, _data) \
GEnum_##eGEnum##_To_Value(_data)
//===============================================
#define GENUM_FROM_VALUE(eGEnum, _data) \
GEnum_##eGEnum##_From_Value(_data)
//===============================================
