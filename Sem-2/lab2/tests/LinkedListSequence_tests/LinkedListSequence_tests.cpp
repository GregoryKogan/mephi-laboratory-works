//
// Created by Gregory Kogan on 07.05.2023.
//

#include "LinkedListSequence_tests.h"


kogan::TestSuite linked_list_sequence_suite("LinkedListSequence");


TEST(linked_list_sequence1, linked_list_sequence_suite) {
    ASSERT(1 + 3 == 4);
}

TEST(linked_list_sequence2, linked_list_sequence_suite) {
    ASSERT(2 + 2 == 4);
}

TEST(linked_list_sequence3, linked_list_sequence_suite) {
    ASSERT(3 - 1 == 2);
}


kogan::TestSuite get_linked_list_sequence_suite() {
    return linked_list_sequence_suite;
}
