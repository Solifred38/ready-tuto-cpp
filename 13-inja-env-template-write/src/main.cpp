//===============================================
#include "GTemplate.h"
//===============================================
int main(int _argc, char** _argv) {
    GTemplate lTemplate;
    lTemplate.setFilename("/home.html");
    lTemplate["name"] = "world";
    lTemplate.write("/home-out.html");
    return 0;
}
//===============================================
