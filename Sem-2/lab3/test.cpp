#include "tests/queue/queue_tests.hpp"


int main() {
    std::vector<kogan::TestSuite> suites = {
            get_queue_test_suite(),
    };

    kogan::Tester tester(suites);
    tester.test();

    return 0;
}
