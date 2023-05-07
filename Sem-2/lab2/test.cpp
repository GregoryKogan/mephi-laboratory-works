#include "tests/ArraySequence_tests/ArraySequence_tests.h"
#include "tests/LinkedListSequence_tests/LinkedListSequence_tests.h"


int main() {
    get_array_sequence_suite().run();
    get_linked_list_sequence_suite().run();
    return 0;
}
