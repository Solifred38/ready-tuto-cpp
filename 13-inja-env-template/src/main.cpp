//===============================================
#include "GTemplate.h"
//===============================================
int main(int _argc, char** _argv) {
    GTemplate lTemplate;
    lTemplate.setFilename("/home.html");
    lTemplate["name"] = "world";
    std::cout << lTemplate.parse().getTemplateText() << std::endl;
    return 0;
}
//===============================================
