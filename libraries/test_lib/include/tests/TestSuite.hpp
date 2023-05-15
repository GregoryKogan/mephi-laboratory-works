//
// Created by Gregory Kogan on 06.05.2023.
//

#ifndef SEQUENCE_LIB_TESTSUITE_HPP
#define SEQUENCE_LIB_TESTSUITE_HPP

#include <vector>
#include "Test.hpp"
#include "../exceptions/AssertionFailedException/AssertionFailedException.hpp"

namespace kogan {

    class TestSuite {
        std::vector<Test> tests;
        std::string name;

    public:
        explicit TestSuite(std::string name);
        size_t add_test(const Test& test);
        int get_tests_count();
        int run();
    };

    #define TEST(name, suite) \
    void suite##_##name(); \
    size_t tmp_##suite##_##name = suite.add_test(kogan::Test(#name, suite##_##name)); \
    void suite##_##name()

    #define ASSERT(expression) \
    if (!(expression)) throw kogan::AssertionFailedException(#expression, __FILE__,  __FUNCTION__, __LINE__)

} // kogan

#endif //SEQUENCE_LIB_TESTSUITE_HPP
