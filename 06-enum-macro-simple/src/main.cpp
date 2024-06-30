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
    std::cout << "Enum_To_String: " << GEnum_eGColor_To_String(GREEN) << std::endl;
    std::cout << "Enum_From_String: " << GEnum_eGColor_To_String(GEnum_eGColor_From_String("Green")) << std::endl;
    return 0;
}
//===============================================
