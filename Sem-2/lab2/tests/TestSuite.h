//
// Created by Gregory Kogan on 06.05.2023.
//

#ifndef SEQUENCE_LIB_TESTSUITE_H
#define SEQUENCE_LIB_TESTSUITE_H

#include <vector>
#include "Test.h"
#include "../exceptions/AssertionFailedException/AssertionFailedException.h"

namespace kogan {

    class TestSuite {
        std::vector<Test> tests;
        std::string name;

    public:
        explicit TestSuite(std::string name);
        size_t add_test(const Test& test);
        bool run();
    };

    #define TEST(name, suite) \
    void name(); \
    size_t tmp_##name = suite.add_test(kogan::Test(#name, name)); \
    void name()

    #define ASSERT(expression) \
    if (!(expression)) \
        throw kogan::AssertionFailedException(#expression, __FILE__, __LINE__);

} // kogan

#endif //SEQUENCE_LIB_TESTSUITE_H
