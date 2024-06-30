//===============================================
#include "GInclude.h"
//===============================================
GENUM_DEFINE(
    eGColor
    , RED
    , GREEN
    , BLUE
)
//===============================================
GENUM_CONVERT(
      eGColor   , std::string
    , {RED      , "Red"}
    , {GREEN    , "Green"}
    , {BLUE     , "Blue"}
)
//===============================================
int main(int _argc, char** _argv) {
    std::cout << "Enum_To_String: " << GENUM_TO_STRING(eGColor, GREEN) << std::endl;
    std::cout << "Enum_To_String: " << GENUM_TO_STRING(eGColor, GENUM_FROM_STRING(eGColor, "Red")) << std::endl;
    std::cout << "Enum_To_String: " << GENUM_TO_STRING(eGColor, RED) << std::endl;
    std::cout << "Enum_To_String: " << GENUM_TO_STRING(eGColor, GENUM_FROM_STRING(eGColor, "Yellow")) << std::endl;
    return 0;
}
//===============================================
