//===============================================
#include "GInclude.h"
//===============================================
GMAP_DEFINE(sChiffreToLettre, int , std::string,
    {0  , "zero"},
    {1  , "Un"},
    {2  , "Deux"},
    {3  , "Trois"}
)
//===============================================
int main(int _argc, char** _argv) {
    std::cout << "GMAP_GET_VALUE : " << GMAP_GET_VALUE(sChiffreToLettre, 0) << std::endl;
    std::cout << "GMAP_GET_KEY : " << GMAP_GET_KEY(sChiffreToLettre, "Un") << std::endl;
    std::cout << "GMAP_GET_VALUE : " << GMAP_GET_VALUE(sChiffreToLettre, 5) << std::endl;
    std::cout << "GMAP_GET_KEY : " << GMAP_GET_KEY(sChiffreToLettre, "Cinq") << std::endl;
    std::cout << "GMAP_GET_VALUE : " << GMAP_EXIST_VALUE(sChiffreToLettre, 0) << std::endl;
    std::cout << "GMAP_EXIST_KEY : " << GMAP_EXIST_KEY(sChiffreToLettre, "Un") << std::endl;
    std::cout << "GMAP_EXIST_VALUE : " << GMAP_EXIST_VALUE(sChiffreToLettre, 5) << std::endl;
    std::cout << "GMAP_EXIST_KEY : " << GMAP_EXIST_KEY(sChiffreToLettre, "Cinq") << std::endl;
    return 0;
}
//===============================================
