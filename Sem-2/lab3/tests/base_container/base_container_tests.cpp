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
    for (auto& x: d)
        x = counter++;

    ASSERT(d.pop_front() == 100);
    ASSERT(d.pop_front() == 101);
    ASSERT(d.pop_back() == 109);
}

TEST(map, base_container_test_suite) {
    int values[10] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    kogan::Deque<int> d(values, 10);

    kogan::Sequence<int>* squares = d.map([](int x) { return x * x; });
    ASSERT(squares->get_length() == 10);
    ASSERT(squares->get(0) == 1);
    ASSERT(squares->get(1) == 4);
    ASSERT(squares->get(2) == 9);
    ASSERT(squares->get(3) == 16);
    ASSERT(squares->get(9) == 100);
    delete squares;

    kogan::Sequence<int>* identity = d.map([](int x) { return x; });
    ASSERT(identity->get_length() == 10);
    ASSERT(identity->get(0) == 1);
    ASSERT(identity->get(1) == 2);
    ASSERT(identity->get(9) == 10);
    delete identity;

    kogan::Sequence<int>* negatives = d.map([](int x) { return -x; });
    ASSERT(negatives->get_length() == 10);
    ASSERT(negatives->get(0) == -1);
    ASSERT(negatives->get(1) == -2);
    ASSERT(negatives->get(9) == -10);
    delete negatives;

    kogan::Sequence<int>* zeros = d.map([](int x) { return 0; });
    ASSERT(zeros->get_length() == 10);
    ASSERT(zeros->get(0) == 0);
    ASSERT(zeros->get(1) == 0);
    ASSERT(zeros->get(9) == 0);
    delete zeros;
}

TEST(where, base_container_test_suite) {
    int values[10] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    kogan::Deque<int> d(values, 10);

    kogan::Sequence<int>* evens = d.where([](int x) { return x % 2 == 0; });
    ASSERT(evens->get_length() == 5);
    ASSERT(evens->get(0) == 2);
    ASSERT(evens->get(1) == 4);
    ASSERT(evens->get(4) == 10);
    delete evens;

    kogan::Sequence<int>* odds = d.where([](int x) { return x % 2 == 1; });
    ASSERT(odds->get_length() == 5);
    ASSERT(odds->get(0) == 1);
    ASSERT(odds->get(1) == 3);
    ASSERT(odds->get(4) == 9);
    delete odds;

    kogan::Sequence<int>* all = d.where([](int x) { return true; });
    ASSERT(all->get_length() == 10);
    ASSERT(all->get(0) == 1);
    ASSERT(all->get(1) == 2);
    ASSERT(all->get(9) == 10);

    kogan::Sequence<int>* none = d.where([](int x) { return false; });
    ASSERT(none->get_length() == 0);
    delete none;

    kogan::Sequence<int>* empty = kogan::Deque<int>().where([](int x) { return true; });
    ASSERT(empty->get_length() == 0);
    delete empty;
}

TEST(reduce, base_container_test_suite) {
    int values[10] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    kogan::Deque<int> d(values, 10);

    int sum = d.reduce([](int a, int b) { return a + b; }, 0);
    ASSERT(sum == 55);

    int product = d.reduce([](int a, int b) { return a * b; }, 1);
    ASSERT(product == 3628800);

    int max = d.reduce([](int a, int b) { return a > b ? a : b; }, INT_MIN);
    ASSERT(max == 10);

    int min = d.reduce([](int a, int b) { return a < b ? a : b;}, INT_MAX);
    ASSERT(min == 1);

    int count = d.reduce([](int a, int b) { return a + 1; }, 0);
    ASSERT(count == 10);

    int sum_of_squares = d.reduce([](int a, int b) { return a + b * b; }, 0);
    ASSERT(sum_of_squares == 385);

    int sum_of_cubes = d.reduce([](int a, int b) { return a + b * b * b; }, 0);
    ASSERT(sum_of_cubes == 3025);
}

TEST(reduce_single_item, base_container_test_suite) {
    kogan::Deque<int> d;
    d.push_back(42);

    int sum = d.reduce([](int a, int b) { return a + b; }, 0);
    ASSERT(sum == 42);

    int product = d.reduce([](int a, int b) { return a * b; }, 1);
    ASSERT(product == 42);

    int max = d.reduce([](int a, int b) { return a > b ? a : b; }, INT_MIN);
    ASSERT(max == 42);

    int min = d.reduce([](int a, int b) { return a < b ? a : b;}, INT_MAX);
    ASSERT(min == 42);

    int count = d.reduce([](int a, int b) { return a + 1; }, 0);
    ASSERT(count == 1);

    int sum_of_squares = d.reduce([](int a, int b) { return a + b * b; }, 0);
    ASSERT(sum_of_squares == 1764);

    int sum_of_cubes = d.reduce([](int a, int b) { return a + b * b * b; }, 0);
    ASSERT(sum_of_cubes == 74088);
}

kogan::TestSuite get_base_container_test_suite() {
    return base_container_test_suite;
}
