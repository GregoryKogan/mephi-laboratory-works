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
    int* values = new int[10];
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
    int* values = new int[10];
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
    int* values = new int[10];
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

TEST(empty, stack_test_suite) {
    kogan::Stack<int> s;
    ASSERT(s.empty());

    s.push(1);
    ASSERT(!s.empty());

    s.pop();
    ASSERT(s.empty());
}

TEST(size, stack_test_suite) {
    kogan::Stack<int> s;
    ASSERT(s.size() == 0); // NOLINT(readability-container-size-empty)

    s.push(1);
    ASSERT(s.size() == 1);

    s.pop();
    ASSERT(s.size() == 0); // NOLINT(readability-container-size-empty)

    for (int i = 0; i < 100; ++i)
        s.push(i);
    ASSERT(s.size() == 100);
}

TEST(swap, stack_test_suite) {
    kogan::Stack<int> s1;
    kogan::Stack<int> s2;

    s1.push(1);
    s1.push(2);
    s1.push(3);

    s2.push(4);
    s2.push(5);

    s1.swap(s2);

    ASSERT(s1.size() == 2);
    ASSERT(s2.size() == 3);

    ASSERT(s1.pop() == 5);
    ASSERT(s1.pop() == 4);

    ASSERT(s2.pop() == 3);
    ASSERT(s2.pop() == 2);
    ASSERT(s2.pop() == 1);
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
    } catch (kogan::EmptyContainerException& e) {
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

TEST(get_subsequence, stack_test_suite) {
    kogan::Stack<int> s;

    s.push(1);
    s.push(2);
    s.push(3);
    s.push(4);
    s.push(5);

    kogan::Sequence<int>* ss = s.get_subsequence(0, 4);
    ASSERT(ss->get_length() == 5);
    ASSERT(ss->get(0) == 5);
    ASSERT(ss->get(4) == 1);
    delete ss;

    ss = s.get_subsequence(1, 3);
    ASSERT(ss->get_length() == 3);
    ASSERT(ss->get(0) == 4);
    ASSERT(ss->get(1) == 3);
    ASSERT(ss->get(2) == 2);
    delete ss;

    ss = s.get_subsequence(2, 2);
    ASSERT(ss->get_length() == 1);
    ASSERT(ss->get(0) == 3);
    delete ss;
}


kogan::TestSuite get_stack_test_suite() {
    return stack_test_suite;
}
