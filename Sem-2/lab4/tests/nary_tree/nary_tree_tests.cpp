//
// Created by Gregory Kogan on 21.05.2023.
//

#include "nary_tree_tests.hpp"


kogan::TestSuite nary_tree_test_suite("NaryTree");


TEST(constructor, nary_tree_test_suite) {
    kogan::NaryTree<int> tree(42, 2);
    ASSERT(tree.size() == 1);
    ASSERT(tree.get_data() == 42);
    ASSERT(tree.children_count() == 0);
    ASSERT(tree.max_children_count() == 2);
}

TEST(add_child, nary_tree_test_suite) {
    kogan::NaryTree<int> tree(42, 2);
    tree.add_child(1);
    tree.add_child(2);
    ASSERT(tree.size() == 3);
    ASSERT(tree.children_count() == 2);
    ASSERT(tree.get_child(0)->get_data() == 1);
    ASSERT(tree.get_child(1)->get_data() == 2);
}

TEST(add_child_IndexOutOfRangeException, nary_tree_test_suite) {
    kogan::NaryTree<int> tree(42, 2);
    tree.add_child(1);
    tree.add_child(2);

    try {
        tree.add_child(3);
        ASSERT(false);
    } catch (kogan::IndexOutOfRangeException &e) {
        ASSERT(true);
    } catch (...) {
        ASSERT(false);
    }
}

TEST(operator_square_brackets, nary_tree_test_suite) {
    kogan::NaryTree<int> tree(42, 2);
    tree.add_child(1);
    tree.add_child(2);
    ASSERT(tree[0].get_data() == 1);
    ASSERT(tree[1].get_data() == 2);

    tree[0].add_child(3);
    tree[0][0].add_child(4);
    tree[0][0][0].add_child(5);
    tree[0][0][0].add_child(6);

    ASSERT(tree[0][0].get_data() == 3);
    ASSERT(tree[0][0][0].get_data() == 4);
    ASSERT(tree[0][0][0][0].get_data() == 5);
    ASSERT(tree[0][0][0][1].get_data() == 6);
}

kogan::TestSuite get_nary_tree_test_suite() {
    return nary_tree_test_suite;
}
