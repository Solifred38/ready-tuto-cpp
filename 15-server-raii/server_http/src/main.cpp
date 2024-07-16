#include "server_http.h"

int main(int _argc, char** _argv) {
    std::shared_ptr<server_http> lProcess = server_http::create(_argc, _argv);
    lProcess->run();
    return 0;
}
