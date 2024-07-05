//===============================================
#include "GTemplate.h"
//===============================================
int main(int _argc, char** _argv) {
    GTemplate lTemplate = GTemplate::create();
    lTemplate["neighbour"]      = "Peter";
    lTemplate["guests"]         = {"Jeff", "Tom", "Patrick"};
    lTemplate["time"]["start"]  = 16;
    lTemplate["time"]["end"]    = 22;

    lTemplate.setTemplateText("{{ guests.1 }}");
    std::cout << lTemplate.render().getTemplateText() << std::endl;

    lTemplate.setTemplateText("{{ time.start }} to {{ time.end + 1 }}pm");
    std::cout << lTemplate.render().getTemplateText() << std::endl;
    return 0;
}
//===============================================
