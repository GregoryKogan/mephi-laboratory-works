#include "tests/DynamicArray_tests/DynamicArray_tests.hpp"
#include "tests/LinkedList_tests/LinkedList_tests.hpp"
#include "tests/ArraySequence_tests/ArraySequence_tests.hpp"
#include "tests/LinkedListSequence_tests/LinkedListSequence_tests.hpp"


int main() {
    bool all_suites_passed = true;

    if (!get_dynamic_array_suite().run()) all_suites_passed = false;
    if (!get_linked_list_suite().run()) all_suites_passed = false;
    if (!get_array_sequence_suite().run()) all_suites_passed = false;
    if (!get_linked_list_sequence_suite().run()) all_suites_passed = false;

    if (all_suites_passed)
        log_green("All tests passed!\n");
    else
        log_red("Some tests failed\n");

    return 0;
}
