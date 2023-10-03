#include "tests/sample_suite.hpp"

int main() {
    std::vector<kogan::TestSuite> suites = {get_sample_test_suite()};

    kogan::Tester tester(suites);
    tester.test();

    return 0;
}
