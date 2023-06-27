#include "tests/ArraySequence_tests/ArraySequence_tests.hpp"
#include "tests/DynamicArray_tests/DynamicArray_tests.hpp"
#include "tests/LinkedListSequence_tests/LinkedListSequence_tests.hpp"
#include "tests/LinkedList_tests/LinkedList_tests.hpp"
#include "tests/Tester.hpp"

int main() {
  std::vector<kogan::TestSuite> suites = {
      get_dynamic_array_suite(),
      get_linked_list_suite(),
      get_array_sequence_suite(),
      get_linked_list_sequence_suite(),
  };

  kogan::Tester tester(suites);
  tester.test();

  return 0;
}
