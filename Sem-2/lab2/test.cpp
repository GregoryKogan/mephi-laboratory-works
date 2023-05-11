#include "tests/DynamicArray_tests/DynamicArray_tests.hpp"
#include "tests/ArraySequence_tests/ArraySequence_tests.hpp"
#include "tests/LinkedListSequence_tests/LinkedListSequence_tests.hpp"


int main() {
    get_dynamic_array_suite().run();
    get_array_sequence_suite().run();
    get_linked_list_sequence_suite().run();
    return 0;
}
