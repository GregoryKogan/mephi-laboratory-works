#include "tests/UniquePtr_tests/UniquePtr_tests.hpp"

int main() {
    std::vector<kogan::TestSuite> suites = {get_unique_ptr_test_suite()};

    kogan::Tester tester(suites);
    tester.test();

    return 0;
}
