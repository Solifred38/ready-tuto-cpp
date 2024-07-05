//===============================================
#include "GTemplate.h"
//===============================================
int main(int _argc, char** _argv) {
    GTemplate lTemplate;
    lTemplate.setTemplateText("Hello {{ name }}!");
    lTemplate["name"] = "world";
    std::cout << lTemplate.render().getTemplateText() << std::endl;
    return 0;
}
//===============================================
