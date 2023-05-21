//
// Created by Gregory Kogan on 21.05.2023.
//

#include "tests/nary_tree/nary_tree_tests.hpp"


int main() {
    std::vector<kogan::TestSuite> suites = {
        get_nary_tree_test_suite(),
    };

    kogan::Tester tester(suites);
    tester.test();

    return 0;
}