#include "tests/ArraySequence_tests/ArraySequence_tests.hpp"
#include "tests/LinkedListSequence_tests/LinkedListSequence_tests.hpp"


int main() {
    get_array_sequence_suite().run();
    get_linked_list_sequence_suite().run();
    return 0;
}
