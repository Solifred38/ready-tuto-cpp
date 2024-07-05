//===============================================
#include "GTemplate.h"
//===============================================
int main(int _argc, char** _argv) {
    GTemplate lTemplate = GTemplate::create();
    GString lTemplateText;

    lTemplate["neighbour"]      = "Peter";
    lTemplate["guests"]         = {"Jeff", "Tom", "Patrick"};
    lTemplate["time"]["start"]  = 16;
    lTemplate["time"]["end"]    = 22;

    lTemplateText = "{{ guests.1 }}";
    std::cout << lTemplate.render(lTemplateText) << std::endl;

    lTemplateText = "{{ time.start }} to {{ time.end + 1 }}pm";
    std::cout << lTemplate.render(lTemplateText) << std::endl;

    lTemplateText = ""
    "## for guest in guests\n"
    "{{ loop.index1 }}: {{ guest }}\n"
    "## endfor\n"
    "";
    std::cout << lTemplate.render(lTemplateText) << std::endl;
    return 0;
}
//===============================================
