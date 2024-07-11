#include "common_test.h"
#include "common_test_win.h"
#include "common_string.h"

common_test::common_test(int _argc, char** _argv)
: m_argc(_argc)
, m_argv(_argv) {

}

common_test::~common_test() {

}

std::shared_ptr<common_test> common_test::create(int _argc, char** _argv) {
#if defined(_WIN32)
    return std::shared_ptr<common_test>(new common_test_win(_argc, _argv));
#endif
    return std::shared_ptr<common_test>(new common_test(_argc, _argv));
}

void common_test::run() {
    init();
    runString();
    runLog();
}

void common_test::runString() {
    {
        common_string lData = "pré-traitement";
        std::cout << lData << std::endl;
    }
}

void common_test::runLog() {
    {
        common_string lStep = "pré-traitement";
        slog(eGERR, "Le processus de calcul a échoué."
        "|step=%s", lStep.c_str());
    }
}
