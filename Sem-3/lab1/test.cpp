#include "tests/SharedPtr_tests/SharedPtr_tests.hpp"
#include "tests/SmartPtrArraySequence_tests/SmartPtrArraySequence_tests.hpp"
#include "tests/SmartPtrDynamicArray_tests/SmartPtrDynamicArray_tests.hpp"
#include "tests/SmartPtrLinkedListSequence_tests/SmartPtrLinkedListSequence_tests.hpp"
#include "tests/SmartPtrLinkedList_tests/SmartPtrLinkedList_tests.hpp"
#include "tests/UniquePtr_tests/UniquePtr_tests.hpp"

int main() {
    std::vector<kogan::TestSuite> suites = {get_unique_ptr_test_suite(),
                                            get_shared_ptr_test_suite(),
                                            get_smart_ptr_dynamic_array_test_suite(),
                                            get_smart_ptr_linked_list_test_suite(),
                                            get_smart_ptr_array_sequence_test_suite(),
                                            get_smart_ptr_linked_list_sequence_test_suite()};

    kogan::Tester tester(suites);
    tester.test();

    return 0;
}
