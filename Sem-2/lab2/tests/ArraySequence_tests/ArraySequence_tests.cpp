//
// Created by Gregory Kogan on 07.05.2023.
//

#include "ArraySequence_tests.h"


kogan::TestSuite array_sequence_suite("ArraySequence");


TEST(array_sequence1, array_sequence_suite) {
    ASSERT(1 + 3 == 4);
}

TEST(array_sequence2, array_sequence_suite) {
    ASSERT(2 + 2 == 5);
}

TEST(array_sequence3, array_sequence_suite) {
    ASSERT(3 - 1 == 2);
}


kogan::TestSuite get_array_sequence_suite() {
    return array_sequence_suite;
}
