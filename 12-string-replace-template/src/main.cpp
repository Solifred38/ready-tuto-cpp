//===============================================
#include "GTemplate.h"
//===============================================
int main(int _argc, char** _argv) {
    GTemplate lTemplate("/home.html");
    std::cout << lTemplate.getTemplateText() << std::endl;

    GTemplate lTemplate2 = lTemplate.parse();
    std::cout << lTemplate2.getTemplateText() << std::endl;

    lTemplate2.addReplaceData("name", "Gerard");
    lTemplate2.addReplaceData("code", "C++");
    GTemplate lTemplate3 = lTemplate2.render();
    std::cout << lTemplate3.getTemplateText() << std::endl;

    lTemplate2.addReplaceData("name", "Bryan");
    lTemplate2.addReplaceData("code", "Java");
    GTemplate lTemplate4 = lTemplate2.render();
    std::cout << lTemplate4.getTemplateText() << std::endl;

    lTemplate4.addReplaceArr("notes", {10, 20, 30});
    lTemplate4.addReplaceObj("hour", {{"hour", 15}, {"minute", 30}, {"second", 25}});
    GTemplate lTemplate5 = lTemplate4.render();
    std::cout << lTemplate5.getTemplateText() << std::endl;

    return 0;
}
//===============================================
