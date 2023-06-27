#include "tests/base_container/base_container_tests.hpp"
#include "tests/deque/deque_tests.hpp"
#include "tests/person/person_tests.hpp"
#include "tests/queue/queue_tests.hpp"
#include "tests/stack/stack_tests.hpp"

int main() {
  std::vector<kogan::TestSuite> suites = {
      get_base_container_test_suite(), get_queue_test_suite(),
      get_stack_test_suite(), get_deque_test_suite(), get_person_test_suite()};

  kogan::Tester tester(suites);
  tester.test();

  return 0;
}
