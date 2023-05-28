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

TEST(constructor_copy, nary_tree_test_suite) {
    kogan::NaryTreeSerializer<char> deserializer("2 F(B(A()D(C()E()))G(I(H())))");
    const kogan::NaryTree<char>* init_tree = deserializer.get_tree();

    kogan::NaryTree<char> tree(*init_tree);

    kogan::NaryTreeSerializer<char> serializer(tree);
    ASSERT(serializer.get_serialized_tree() == deserializer.get_serialized_tree());
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

    kogan::NaryTreeSerializer<char> serializer(tree);
    ASSERT(serializer.get_serialized_tree() == "2 F(B(A()D(C()E()))G(I(H())))");
}

TEST(serialize_single_element, nary_tree_test_suite) {
    kogan::NaryTree<int> tree(42, 42);

    kogan::NaryTreeSerializer<int> serializer(tree);
    ASSERT(serializer.get_serialized_tree() == "42 42()");
}

TEST(deserialize, nary_tree_test_suite) {
    kogan::NaryTreeSerializer<char> deserializer("2 F(B(A()D(C()E()))G(I(H())))");
    kogan::NaryTreeSerializer<char> serializer(*deserializer.get_tree());
    ASSERT(serializer.get_serialized_tree() == "2 F(B(A()D(C()E()))G(I(H())))");
}

TEST(deserialize_single_element, nary_tree_test_suite) {
    kogan::NaryTreeSerializer<int> deserializer("42 42()");
    kogan::NaryTreeSerializer<int> serializer(*deserializer.get_tree());
    ASSERT(serializer.get_serialized_tree() == "42 42()");
}

TEST(deserialize_strings, nary_tree_test_suite) {
    kogan::NaryTreeSerializer<std::string> deserializer("42 ABC()");
    kogan::NaryTreeSerializer<std::string> serializer(*deserializer.get_tree());
    ASSERT(serializer.get_serialized_tree() == "42 ABC()");
}

TEST(deserialize_strings_with_numbers, nary_tree_test_suite) {
    kogan::NaryTreeSerializer<std::string> deserializer("42 12ABC()");
    kogan::NaryTreeSerializer<std::string> serializer(*deserializer.get_tree());
    ASSERT(serializer.get_serialized_tree() == "42 12ABC()");
}

TEST(deserialize_invalid, nary_tree_test_suite) {
    try {
        kogan::NaryTreeSerializer<int> serializer("42 A(((()");
        ASSERT(false);
    } catch (kogan::InvalidArgumentException& e) {
        ASSERT(true);
    } catch (...) {
        ASSERT(false);
    }

    try {
        kogan::NaryTreeSerializer<int> serializer("42 A()");
        ASSERT(false);
    } catch (kogan::InvalidArgumentException& e) {
        ASSERT(true);
    } catch (...) {
        ASSERT(false);
    }

    try {
        kogan::NaryTreeSerializer<int> serializer("2 F(B(A(), D(C()E(, )))G(I(H())))");
        ASSERT(false);
    } catch (kogan::InvalidArgumentException& e) {
        ASSERT(true);
    } catch (...) {
        ASSERT(false);
    }

    try {
        kogan::NaryTreeSerializer<int> serializer("jkdnkfjng");
        ASSERT(false);
    } catch (kogan::InvalidArgumentException& e) {
        ASSERT(true);
    } catch (...) {
        ASSERT(false);
    }
}

TEST(map, nary_tree_test_suite) {
    kogan::NaryTreeSerializer<int> deserializer("2 1(2(3()4(5()6()))7(8(9())))");

    kogan::NaryTree<int>* mapped_tree = deserializer.get_tree()->map([](int x) { return x * 2; });

    kogan::NaryTreeSerializer<int> serializer(*mapped_tree);
    ASSERT(serializer.get_serialized_tree() == "2 2(4(6()8(10()12()))14(16(18())))");
    delete mapped_tree;
}

TEST(where, nary_tree_test_suite) {
    kogan::NaryTreeSerializer<int> deserializer("2 1(2(3()4(5()6()))7(8(9())))");

    kogan::NaryTree<int>* filtered_tree = deserializer.get_tree()->where([](int x) { return x < 6; });

    kogan::NaryTreeSerializer<int> serializer(*filtered_tree);
    ASSERT(serializer.get_serialized_tree() == "2 1(2(3()4(5())))");
    delete filtered_tree;
}

TEST(count, nary_tree_test_suite) {
    kogan::NaryTreeSerializer<int> deserializer("2 1(2(3()4(5()6()))7(3(9())))");

    ASSERT(deserializer.get_tree()->count(3) == 2);
    ASSERT(deserializer.get_tree()->count(7) == 1);
    ASSERT(deserializer.get_tree()->count(42) == 0);
}

TEST(contains, nary_tree_test_suite) {
    kogan::NaryTreeSerializer<int> superset("2 1(2(3()4(5()6()))7(3(9())))");
    kogan::NaryTreeSerializer<int> subset_1("2 7(3(9()))");
    kogan::NaryTreeSerializer<int> subset_2("2 4(5()6())");
    kogan::NaryTreeSerializer<int> not_subset_1("2 4(7()6())");
    kogan::NaryTreeSerializer<int> not_subset_2("2 4()");

    ASSERT(superset.get_tree()->contains(*superset.get_tree()));
    ASSERT(superset.get_tree()->contains(*subset_1.get_tree()));
    ASSERT(superset.get_tree()->contains(*subset_2.get_tree()));
    ASSERT(!superset.get_tree()->contains(*not_subset_1.get_tree()));
    ASSERT(!superset.get_tree()->contains(*not_subset_2.get_tree()));
}

kogan::TestSuite get_nary_tree_test_suite() {
    return nary_tree_test_suite;
}
