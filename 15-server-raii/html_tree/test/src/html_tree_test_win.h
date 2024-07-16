#pragma once

#include "html_tree_test.h"

class html_tree_test_win : public html_tree_test {
    friend class html_tree_test;

private:
    html_tree_test_win(int _argc, char** _argv);

public:
    ~html_tree_test_win();
    void init();
};
