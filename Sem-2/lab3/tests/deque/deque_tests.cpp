//
// Created by Gregory Kogan on 16.05.2023.
//

#include "deque_tests.hpp"


kogan::TestSuite deque_test_suite("Deque");


TEST(empty_constructor, deque_test_suite) {
    kogan::Deque<int> d;

    ASSERT(d.size() == 0); // NOLINT(readability-container-size-empty)
    ASSERT(d.empty());
}

TEST(array_constructor, deque_test_suite) {
    int* values = new int[10];
    for (int i = 0; i < 10; ++i)
        values[i] = i + 1;

    kogan::Deque<int> d(values, 10);
    delete[] values;

    ASSERT(d.size() == 10);
    ASSERT(!d.empty());
    ASSERT(d.pop_front() == 1);
    ASSERT(d.pop_front() == 2);
    ASSERT(d.pop_back() == 10);
    ASSERT(d.pop_back() == 9);
}

TEST(sequence_constructor, deque_test_suite) {
    int* values = new int[10];
    for (int i = 0; i < 10; ++i)
        values[i] = i + 1;

    kogan::ArraySequence<int> init_seq(values, 10);
    kogan::Deque<int> d(&init_seq);
    delete[] values;

    ASSERT(d.size() == init_seq.get_length());
    ASSERT(d.size() == 10);
    ASSERT(!d.empty());
    ASSERT(d.pop_front() == 1);
    ASSERT(d.pop_front() == init_seq[1]);
    ASSERT(d.pop_back() == 10);
    ASSERT(d.pop_back() == init_seq[8]);
}

TEST(deque_constructor, deque_test_suite) {
    int* values = new int[10];
    for (int i = 0; i < 10; ++i)
        values[i] = i + 1;

    kogan::Deque<int> init_d(values, 10);
    kogan::Deque<int> d(&init_d);
    delete[] values;

    ASSERT(d.size() == init_d.size());
    ASSERT(d.size() == 10);
    ASSERT(!d.empty());
    ASSERT(d.pop_front() == 1);
    ASSERT(init_d.pop_front() == 1);
    ASSERT(d.pop_back() == 10);
    ASSERT(init_d.pop_back() == 10);
    ASSERT(d.pop_front() == init_d.pop_front());
    ASSERT(d.pop_back() == init_d.pop_back());
}

TEST(empty, deque_test_suite) {
    kogan::Deque<int> d;
    ASSERT(d.empty());

    d.push_front(1);
    ASSERT(!d.empty());

    d.pop_back();
    ASSERT(d.empty());
}

TEST(size, deque_test_suite) {
    kogan::Deque<int> d;
    ASSERT(d.size() == 0); // NOLINT(readability-container-size-empty)

    d.push_front(1);
    ASSERT(d.size() == 1);

    d.push_back(2);
    ASSERT(d.size() == 2);

    d.pop_front();
    ASSERT(d.size() == 1);

    d.pop_back();
    ASSERT(d.size() == 0); // NOLINT(readability-container-size-empty)
}

TEST(swap, deque_test_suite) {
    kogan::Deque<int> d1;
    kogan::Deque<int> d2;

    d1.push_front(1);
    d1.push_front(2);
    d1.push_front(3);

    d2.push_back(1);
    d2.push_back(2);
    d2.push_back(3);

    d1.swap(d2);

    ASSERT(d1.pop_front() == 1);
    ASSERT(d1.pop_front() == 2);
    ASSERT(d1.pop_front() == 3);

    ASSERT(d2.pop_front() == 3);
    ASSERT(d2.pop_front() == 2);
    ASSERT(d2.pop_front() == 1);
}

TEST(push_front, deque_test_suite) {
    kogan::Deque<int> d;

    d.push_front(1);
    ASSERT(d.pop_front() == 1);

    d.push_front(2);
    d.push_front(3);
    ASSERT(d.pop_front() == 3);
    ASSERT(d.pop_front() == 2);
}

TEST(push_back, deque_test_suite) {
    kogan::Deque<int> d;

    d.push_back(1);
    ASSERT(d.pop_back() == 1);

    d.push_back(2);
    d.push_back(3);
    ASSERT(d.pop_back() == 3);
    ASSERT(d.pop_back() == 2);
}

TEST(pop_front, deque_test_suite) {
    kogan::Deque<int> d;

    d.push_front(1);
    d.push_front(2);
    d.push_front(3);

    ASSERT(d.pop_front() == 3);
    ASSERT(d.pop_front() == 2);
    ASSERT(d.pop_front() == 1);
}

TEST(pop_back, deque_test_suite) {
    kogan::Deque<int> d;

    d.push_back(1);
    d.push_back(2);
    d.push_back(3);

    ASSERT(d.pop_back() == 3);
    ASSERT(d.pop_back() == 2);
    ASSERT(d.pop_back() == 1);
}

TEST(pop_front_EmptyContainerException, deque_test_suite) {
    kogan::Deque<int> d;

    bool emptyContainerExceptionThrown = false;
    try {
        d.pop_front();
    } catch (kogan::EmptyContainerException& e) {
        emptyContainerExceptionThrown = true;
    }
    ASSERT(emptyContainerExceptionThrown);
}

TEST(pop_back_EmptyContainerException, deque_test_suite) {
    kogan::Deque<int> d;

    bool emptyContainerExceptionThrown = false;
    try {
        d.pop_back();
    } catch (kogan::EmptyContainerException& e) {
        emptyContainerExceptionThrown = true;
    }
    ASSERT(emptyContainerExceptionThrown);
}

TEST(concat, deque_test_suite) {
    kogan::Deque<int> d1;
    kogan::Deque<int> d2;

    d1.push_back(1);
    d1.push_back(2);
    d1.push_back(3);

    d2.push_back(4);
    d2.push_back(5);
    d2.push_back(6);

    auto d3 = d1.concat(d2);

    ASSERT(d3->pop_front() == 1);
    ASSERT(d3->pop_front() == 2);
    ASSERT(d3->pop_front() == 3);
    ASSERT(d3->pop_front() == 4);
    ASSERT(d3->pop_front() == 5);
    ASSERT(d3->pop_front() == 6);
}

TEST(get_subsequence, deque_test_suite) {
    kogan::Deque<int> d;

    d.push_back(1);
    d.push_back(2);
    d.push_back(3);
    d.push_back(4);
    d.push_back(5);

    kogan::Sequence<int>* sq = d.get_subsequence(0, 4);
    ASSERT(sq->get_length() == 5);
    ASSERT(sq->get(0) == 1);
    ASSERT(sq->get(4) == 5);
    delete sq;

    sq = d.get_subsequence(1, 3);
    ASSERT(sq->get_length() == 3);
    ASSERT(sq->get(0) == 2);
    ASSERT(sq->get(1) == 3);
    ASSERT(sq->get(2) == 4);
    delete sq;

    sq = d.get_subsequence(2, 2);
    ASSERT(sq->get_length() == 1);
    ASSERT(sq->get(0) == 3);
    delete sq;
}


kogan::TestSuite get_deque_test_suite() {
    return deque_test_suite;
}