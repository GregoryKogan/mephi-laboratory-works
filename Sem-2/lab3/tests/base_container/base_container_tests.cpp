//
// Created by Gregory Kogan on 20.05.2023.
//

#include "base_container_tests.hpp"


kogan::TestSuite base_container_test_suite("Base container");


TEST(empty, base_container_test_suite) {
    kogan::Deque<int> d;
    ASSERT(d.empty());

    d.push_front(1);
    ASSERT(!d.empty());

    d.pop_back();
    ASSERT(d.empty());
}

TEST(size, base_container_test_suite) {
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

TEST(swap, base_container_test_suite) {
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

TEST(get_subsequence, base_container_test_suite) {
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

TEST(range_based_for_loop, base_container_test_suite) {
    int values[10] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    kogan::Deque<int> d(values, 10);

    for (auto x: d)
        ASSERT(x == values[x - 1]);
}

TEST(range_based_for_loop_assignment, base_container_test_suite) {
    int values[10] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    kogan::Deque<int> d(values, 10);

    int counter = 100;
    for (auto x: d) {
        x = counter;
        counter++;
    }

    ASSERT(d.pop_front() == 100);
    ASSERT(d.pop_front() == 101);
    ASSERT(d.pop_back() == 109);
}


kogan::TestSuite get_base_container_test_suite() {
    return base_container_test_suite;
}
