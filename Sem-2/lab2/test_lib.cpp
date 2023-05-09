//
// Created by Gregory Kogan on 10.05.2023.
//

#include "test_lib.h"


kogan::TestSuite test_lib_suite("TestLib");


TEST(test_lib, test_lib_suite) {
    ASSERT(true);
}


void test_lib_is_working() {
    std::cout << "Test lib is working!" << std::endl;

    test_lib_suite.run();
}
