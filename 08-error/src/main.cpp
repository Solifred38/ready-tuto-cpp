//===============================================
#include "GError.h"
//===============================================
int main(int _argc, char** _argv) {
    GError lErrors;
    lErrors.addProblem();
    lErrors.addError("Erreur lors du chargement des paramètres.");
    GError lErrors2;
    lErrors2.addError("Erreur lors de la connexion au serveur.");
    lErrors2.addErrors(lErrors);
    std::cout << lErrors2.size() << std::endl;
    lErrors2.showErrors();
    return 0;
}
//===============================================
