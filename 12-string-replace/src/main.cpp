//===============================================
#include "GReplace.h"
//===============================================
int main(int _argc, char** _argv) {
    GString lData = ""
    "Bonjour {{m_name}}, Ton code est {{m_code}}."
    "";
    GReplace lReplace(lData);
    lReplace.addReplace("m_name", "Gerard");
    lReplace.addReplace("m_code", "C++");
    lReplace.run();
    std::cout << lReplace.getResultText() << std::endl;
    return 0;
}
//===============================================
