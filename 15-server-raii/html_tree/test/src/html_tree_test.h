#pragma once

#include "html_tree_test_header.h"

class html_tree_test : public common_object {
protected:
    html_tree_test(int _argc, char** _argv);

public:
    ~html_tree_test();
    static std::shared_ptr<html_tree_test> create(int _argc, char** _argv);
    virtual void init() {}
    void run();

private:
    void runTest();

private:
    int m_argc;
    char** m_argv;
};
