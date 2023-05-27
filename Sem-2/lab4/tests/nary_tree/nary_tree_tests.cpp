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

TEST(constructor_without_max_children, nary_tree_test_suite) {
    kogan::NaryTree<int> tree(42);
    ASSERT(tree.size() == 1);
    ASSERT(tree.get_data() == 42);
    ASSERT(tree.children_count() == 0);
    ASSERT(tree.max_children_count() > 1e9);
}

TEST(height, nary_tree_test_suite) {
    kogan::NaryTree<char> tree('F', 2);
    tree.add_child('B');
    tree.add_child('G');
    tree[0].add_child('A');
    tree[0].add_child('D');
    tree[0][1].add_child('C');
    tree[0][1].add_child('E');
    tree[1].add_child('I');
    tree[1][0].add_child('H');

    ASSERT(tree.height() == 4);
}

TEST(height_single_element, nary_tree_test_suite) {
    kogan::NaryTree<char> tree('F', 2);

    ASSERT(tree.height() == 1);
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

TEST(set_data, nary_tree_test_suite) {
    kogan::NaryTree<int> tree(42, 2);
    tree.set_data(1);
    ASSERT(tree.get_data() == 1);
}

TEST(traverse, nary_tree_test_suite) {
    kogan::NaryTree<char> tree('F', 2);
    tree.add_child('B');
    tree.add_child('G');
    tree[0].add_child('A');
    tree[0].add_child('D');
    tree[0][1].add_child('C');
    tree[0][1].add_child('E');
    tree[1].add_child('I');
    tree[1][0].add_child('H');

    kogan::Sequence<char>* default_path = tree.traverse();
    char default_target[10] = "FBADCEGIH";

    ASSERT(default_path->get_length() == 9);
    for (int i = 0; i < 9; ++i)
        ASSERT(default_path->get(i) == default_target[i]);
    delete default_path;
}

TEST(traverse_ROOT_LEFT_RIGHT, nary_tree_test_suite) {
    kogan::NaryTree<char> tree('F', 2);
    tree.add_child('B');
    tree.add_child('G');
    tree[0].add_child('A');
    tree[0].add_child('D');
    tree[0][1].add_child('C');
    tree[0][1].add_child('E');
    tree[1].add_child('I');
    tree[1][0].add_child('H');

    kogan::Sequence<char>* path_root_left_right =
            tree.traverse(kogan::NaryTree<char>::TraverseType::ROOT_LEFT_RIGHT);
    char root_left_right_target[10] = "FBADCEGIH";

    ASSERT(path_root_left_right->get_length() == 9);
    for (int i = 0; i < 9; ++i)
        ASSERT(path_root_left_right->get(i) == root_left_right_target[i]);
    delete path_root_left_right;
}

TEST(traverse_ROOT_RIGHT_LEFT, nary_tree_test_suite) {
    kogan::NaryTree<char> tree('F', 2);
    tree.add_child('B');
    tree.add_child('G');
    tree[0].add_child('A');
    tree[0].add_child('D');
    tree[0][1].add_child('C');
    tree[0][1].add_child('E');
    tree[1].add_child('I');
    tree[1][0].add_child('H');

    kogan::Sequence<char>* path_root_right_left =
            tree.traverse(kogan::NaryTree<char>::TraverseType::ROOT_RIGHT_LEFT);
    char root_right_left_target[10] = "FGIHBDECA";

    ASSERT(path_root_right_left->get_length() == 9);
    for (int i = 0; i < 9; ++i)
        ASSERT(path_root_right_left->get(i) == root_right_left_target[i]);
    delete path_root_right_left;
}

TEST(traverse_LEFT_RIGHT_ROOT, nary_tree_test_suite) {
    kogan::NaryTree<char> tree('F', 2);
    tree.add_child('B');
    tree.add_child('G');
    tree[0].add_child('A');
    tree[0].add_child('D');
    tree[0][1].add_child('C');
    tree[0][1].add_child('E');
    tree[1].add_child('I');
    tree[1][0].add_child('H');

    kogan::Sequence<char>* path_left_right_root =
            tree.traverse(kogan::NaryTree<char>::TraverseType::LEFT_RIGHT_ROOT);
    char left_right_root_target[10] = "ACEDBHIGF";

    ASSERT(path_left_right_root->get_length() == 9);
    for (int i = 0; i < 9; ++i)
        ASSERT(path_left_right_root->get(i) == left_right_root_target[i]);
    delete path_left_right_root;
}

TEST(traverse_RIGHT_LEFT_ROOT, nary_tree_test_suite) {
    kogan::NaryTree<char> tree('F', 2);
    tree.add_child('B');
    tree.add_child('G');
    tree[0].add_child('A');
    tree[0].add_child('D');
    tree[0][1].add_child('C');
    tree[0][1].add_child('E');
    tree[1].add_child('I');
    tree[1][0].add_child('H');

    kogan::Sequence<char>* path_right_left_root =
            tree.traverse(kogan::NaryTree<char>::TraverseType::RIGHT_LEFT_ROOT);
    char right_left_root_target[10] = "HIGECDABF";

    ASSERT(path_right_left_root->get_length() == 9);
    for (int i = 0; i < 9; ++i)
        ASSERT(path_right_left_root->get(i) == right_left_root_target[i]);
    delete path_right_left_root;
}

TEST(to_string, nary_tree_test_suite) {
    kogan::NaryTree<char> tree('F', 2);
    tree.add_child('B');
    tree.add_child('G');
    tree[0].add_child('A');
    tree[0].add_child('D');
    tree[0][1].add_child('C');
    tree[0][1].add_child('E');
    tree[1].add_child('I');
    tree[1][0].add_child('H');

    ASSERT(tree.to_string() ==
        "[F, B, A, D, C, E, G, I, H]");
    ASSERT(tree.to_string(kogan::NaryTree<char>::TraverseType::ROOT_LEFT_RIGHT) ==
        "[F, B, A, D, C, E, G, I, H]");
    ASSERT(tree.to_string(kogan::NaryTree<char>::TraverseType::ROOT_RIGHT_LEFT) ==
        "[F, G, I, H, B, D, E, C, A]");
    ASSERT(tree.to_string(kogan::NaryTree<char>::TraverseType::LEFT_RIGHT_ROOT) ==
        "[A, C, E, D, B, H, I, G, F]");
    ASSERT(tree.to_string(kogan::NaryTree<char>::TraverseType::RIGHT_LEFT_ROOT) ==
        "[H, I, G, E, C, D, A, B, F]");
}

TEST(serialize, nary_tree_test_suite) {
    kogan::NaryTree<char> tree('F', 2);
    tree.add_child('B');
    tree.add_child('G');
    tree[0].add_child('A');
    tree[0].add_child('D');
    tree[0][1].add_child('C');
    tree[0][1].add_child('E');
    tree[1].add_child('I');
    tree[1][0].add_child('H');

    ASSERT(tree.serialize() == "2 F(B(A()D(C()E()))G(I(H())))");
}

TEST(serialize_single_element, nary_tree_test_suite) {
    kogan::NaryTree<int> tree(42, 42);

    ASSERT(tree.serialize() == "42 42()");
}

TEST(deserialize, nary_tree_test_suite) {
    kogan::NaryTree<char>* tree = kogan::NaryTree<char>::deserialize("2 F(B(A()D(C()E()))G(I(H())))");

    ASSERT(tree->serialize() == "2 F(B(A()D(C()E()))G(I(H())))");
    delete tree;
}

TEST(deserialize_single_element, nary_tree_test_suite) {
    kogan::NaryTree<int>* tree = kogan::NaryTree<int>::deserialize("42 42()");

    ASSERT(tree->serialize() == "42 42()");
    delete tree;
}

TEST(deserialize_strings, nary_tree_test_suite) {
    kogan::NaryTree<std::string>* tree = kogan::NaryTree<std::string>::deserialize("42 ABC()");

    ASSERT(tree->serialize() == "42 ABC()");

    delete tree;
}

TEST(deserialize_invalid, nary_tree_test_suite) {
    try {
        kogan::NaryTree<char>* tree = kogan::NaryTree<char>::deserialize("42 A(((()");
        delete tree;
        ASSERT(false);
    } catch (kogan::InvalidArgumentException& e) {
        ASSERT(true);
    }

    try {
        kogan::NaryTree<int>* tree = kogan::NaryTree<int>::deserialize("42 A()");
        delete tree;
        ASSERT(false);
    } catch (kogan::InvalidArgumentException& e) {
        ASSERT(true);
    }

    try {
        kogan::NaryTree<int>* tree = kogan::NaryTree<int>::deserialize("2 F(B(A(), D(C()E(, )))G(I(H())))");
        delete tree;
        ASSERT(false);
    } catch (kogan::InvalidArgumentException& e) {
        ASSERT(true);
    }

    try {
        kogan::NaryTree<int>* tree = kogan::NaryTree<int>::deserialize("jkdnkfjng");
        delete tree;
        ASSERT(false);
    } catch (kogan::InvalidArgumentException& e) {
        ASSERT(true);
    }
}

kogan::TestSuite get_nary_tree_test_suite() {
    return nary_tree_test_suite;
}
