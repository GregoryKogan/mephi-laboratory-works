#include "sample_suite.hpp"

kogan::TestSuite sample_test_suite("Sample test suite");

TEST(ok_test, sample_test_suite) {
    ASSERT(1 == 1);
}

TEST(fail_test, sample_test_suite) {
    ASSERT(1 == 2);
}

kogan::TestSuite get_sample_test_suite() { return sample_test_suite; }
