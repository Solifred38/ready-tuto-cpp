//===============================================
#include "GTemplate.h"
//===============================================
int main(int _argc, char** _argv) {
    SetConsoleOutputCP(CP_UTF8);
    GTemplate lTemplate("/home.html");
    lTemplate.addReplaceObj("lettres", {
          {"10"     , "Dix"}
        , {"1000"   , "Mille"}
        , {"100000" , "Dix-mille"}
    });
    lTemplate = lTemplate.parse();
    lTemplate = lTemplate.render();
    std::cout << lTemplate.getTemplateText() << std::endl;
    return 0;
}
//===============================================
