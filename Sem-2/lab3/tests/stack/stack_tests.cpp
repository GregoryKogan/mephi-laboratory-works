//
// Created by Gregory Kogan on 16.05.2023.
//

#include "stack_tests.hpp"

kogan::TestSuite stack_test_suite("Stack");

TEST(empty_constructor, stack_test_suite) {
  kogan::Stack<int> s;

  ASSERT(s.size() == 0); // NOLINT(readability-container-size-empty)
  ASSERT(s.empty());
}

TEST(array_constructor, stack_test_suite) {
  int *values = new int[10];
  for (int i = 0; i < 10; ++i)
    values[i] = i + 1;

  kogan::Stack<int> s(values, 10);
  delete[] values;

  ASSERT(s.size() == 10);
  ASSERT(!s.empty());
  ASSERT(s.pop() == 1);
  ASSERT(s.pop() == 2);
}

TEST(sequence_constructor, stack_test_suite) {
  int *values = new int[10];
  for (int i = 0; i < 10; ++i)
    values[i] = i + 1;

  kogan::ArraySequence<int> init_seq(values, 10);
  kogan::Stack<int> s(&init_seq);
  delete[] values;

  ASSERT(s.size() == init_seq.get_length());
  ASSERT(s.size() == 10);
  ASSERT(!s.empty());
  ASSERT(s.pop() == 1);
  ASSERT(s.pop() == init_seq[1]);
}

TEST(stack_constructor, stack_test_suite) {
  int *values = new int[10];
  for (int i = 0; i < 10; ++i)
    values[i] = i + 1;

  kogan::Stack<int> init_s(values, 10);
  kogan::Stack<int> s(&init_s);
  delete[] values;

  ASSERT(s.size() == init_s.size());
  ASSERT(s.size() == 10);
  ASSERT(!s.empty());
  ASSERT(s.pop() == 1);
  ASSERT(init_s.pop() == 1);
  ASSERT(s.pop() == init_s.pop());
}

TEST(push, stack_test_suite) {
  kogan::Stack<int> s;

  s.push(1);
  ASSERT(s.size() == 1);
  ASSERT(s.pop() == 1);

  s.push(2);
  s.push(3);
  ASSERT(s.size() == 2);
  ASSERT(s.pop() == 3);
  ASSERT(s.pop() == 2);
}

TEST(pop, stack_test_suite) {
  kogan::Stack<int> s;

  s.push(1);
  s.push(2);
  s.push(3);

  ASSERT(s.pop() == 3);
  ASSERT(s.pop() == 2);
  ASSERT(s.pop() == 1);
}

TEST(pop_EmptyContainerException, stack_test_suite) {
  kogan::Stack<int> s;

  bool emptyContainerExceptionThrown = false;
  try {
    s.pop();
  } catch (kogan::EmptyContainerException &e) {
    emptyContainerExceptionThrown = true;
  }
  ASSERT(emptyContainerExceptionThrown);
}

TEST(concat, stack_test_suite) {
  kogan::Stack<int> s1;
  kogan::Stack<int> s2;

  s1.push(1);
  s1.push(2);
  s1.push(3);

  s2.push(4);
  s2.push(5);

  auto s3 = s1.concat(s2);

  ASSERT(s1.size() == 3);
  ASSERT(s2.size() == 2);

  ASSERT(s3->size() == 5);
  ASSERT(s3->pop() == 3);
  ASSERT(s3->pop() == 2);
  ASSERT(s3->pop() == 1);
  ASSERT(s3->pop() == 5);
  ASSERT(s3->pop() == 4);
  ASSERT(s3->empty());
  delete s3;

  auto s4 = s2.concat(s1);

  ASSERT(s1.size() == 3);
  ASSERT(s2.size() == 2);

  ASSERT(s4->size() == 5);
  ASSERT(s4->pop() == 5);
  ASSERT(s4->pop() == 4);
  ASSERT(s4->pop() == 3);
  ASSERT(s4->pop() == 2);
  ASSERT(s4->pop() == 1);
  ASSERT(s4->empty());
  delete s4;
}

kogan::TestSuite get_stack_test_suite() { return stack_test_suite; }
