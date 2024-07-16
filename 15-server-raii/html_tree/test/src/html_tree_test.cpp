#include "html_tree_test.h"
#include "html_tree_test_win.h"
#include "html_tree.h"

html_tree_test::html_tree_test(int _argc, char** _argv)
: m_argc(_argc)
, m_argv(_argv) {

}

html_tree_test::~html_tree_test() {

}

std::shared_ptr<html_tree_test> html_tree_test::create(int _argc, char** _argv) {
#if defined(_WIN32)
    return std::shared_ptr<html_tree_test>(new html_tree_test_win(_argc, _argv));
#endif
    return std::shared_ptr<html_tree_test>(new html_tree_test(_argc, _argv));
}

void html_tree_test::run() {
    init();
    runTest();
}

void html_tree_test::runTest() {
    common_string lDataJson = "[{\"index\": 1,\"parent_index\": 0,\"name\": \"Element_1\",\"type\": \"dir\"  },  {\"index\": 2,\"parent_index\": 1,\"name\": \"Element_1.1\",\"type\": \"file\"  },  {\"index\": 3,\"parent_index\": 1,\"name\": \"Element_1.2\",\"type\": \"file\"  },  {\"index\": 4,\"parent_index\": 1,\"name\": \"Element_1.3\",\"type\": \"dir\"  },  {\"index\": 5,\"parent_index\": 4,\"name\": \"Element_1.3.1\",\"type\": \"file\"  },  {\"index\": 6,\"parent_index\": 4,\"name\": \"Element_1.3.2\",\"type\": \"file\"  },  {\"index\": 7,\"parent_index\": 4,\"name\": \"Element_1.3.3\",\"type\": \"dir\"  },  {\"index\": 8,\"parent_index\": 7,\"name\": \"Element_1.3.3.1\",\"type\": \"file\"  },  {\"index\": 9,\"parent_index\": 7,\"name\": \"Element_1.3.3.2\",\"type\": \"file\"  },  {\"index\": 10,\"parent_index\": 7,\"name\": \"Element_1.3.3.3\",\"type\": \"file\"  },  {\"index\": 11,\"parent_index\": 7,\"name\": \"Element_1.3.3.4\",\"type\": \"file\"  },  {\"index\": 12,\"parent_index\": 4,\"name\": \"Element_1.3.4\",\"type\": \"file\"  },  {\"index\": 13,\"parent_index\": 4,\"name\": \"Element_1.3.5\",\"type\": \"file\"  },  {\"index\": 14,\"parent_index\": 1,\"name\": \"Element_1.4\",\"type\": \"file\"  },  {\"index\": 15,\"parent_index\": 1,\"name\": \"Element_1.5\",\"type\": \"file\"  },  {\"index\": 16,\"parent_index\": 0,\"name\": \"Element_2\",\"type\": \"file\"  },  {\"index\": 17,\"parent_index\": 0,\"name\": \"Element_3\",\"type\": \"file\"}]";
    html_tree lTree(lDataJson);
    lTree.saveTree();
}
