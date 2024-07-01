//===============================================
#include "GTemplate.h"
//===============================================
int main(int _argc, char** _argv) {
    SetConsoleOutputCP(CP_UTF8);
    GTemplate lTemplate("/home.html");
    lTemplate.addReplaceArr("names", {"Bryan", "Marion", "Sephora"});
    lTemplate = lTemplate.parse();
    lTemplate = lTemplate.render();
    std::cout << lTemplate.getTemplateText() << std::endl;
    return 0;
}
//===============================================
