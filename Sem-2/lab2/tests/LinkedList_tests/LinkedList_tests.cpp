//
// Created by Gregory Kogan on 11.05.2023.
//

#include "LinkedList_tests.hpp"


kogan::TestSuite linked_list_suite("LinkedList");


TEST(array_constructor, linked_list_suite) {
    int* values = new int[10];
    for (int i = 0; i < 10; ++i)
        values[i] = i + 1;
    kogan::LinkedList<int> list(values, 10);
    delete[] values;

    ASSERT(list.get_length() == 10);
    ASSERT(list.get(0) == 1);
    ASSERT(list.get(2) == 3);
    ASSERT(list.get(9) == 10);
}

TEST(empty_constructor, linked_list_suite) {
    kogan::LinkedList<int> list;

    ASSERT(list.get_length() == 0);
}

TEST(linked_list_constructor, linked_list_suite) {
    int* values = new int[10];
    for (int i = 0; i < 10; ++i)
        values[i] = i + 1;

    kogan::LinkedList<int> init_list(values, 10);
    kogan::LinkedList<int> list(init_list);
    delete[] values;

    ASSERT(list.get_length() == init_list.get_length());
    ASSERT(list.get_length() == 10);
    ASSERT(list.get(0) == 1);
    ASSERT(list.get(2) == 3);
    ASSERT(list.get(9) == 10);
    ASSERT(list.get(0) == init_list.get(0));
    ASSERT(list.get(2) == init_list.get(2));
    ASSERT(list.get(9) == init_list.get(9));
}

TEST(get_first, linked_list_suite) {
    kogan::LinkedList<int> list;
    for (int i = 0; i < 10; ++i)
        list.append(i + 1);

    ASSERT(list.get_first() == list.get(0));
    ASSERT(list.get_first() == 1);
}

TEST(get_first_single_item, linked_list_suite) {
    int* values = new int[1];
    values[0] = 42;
    kogan::LinkedList<int> list(values, 1);
    delete[] values;

    ASSERT(list.get_first() == list.get(0));
    ASSERT(list.get_first() == 42);
}

TEST(get_last, linked_list_suite) {
    kogan::LinkedList<int> list;
    for (int i = 0; i < 10; ++i)
        list.append(i + 1);

    ASSERT(list.get_last() == list.get(list.get_length() - 1));
    ASSERT(list.get_last() == 10);
}

TEST(get_last_single_item, linked_list_suite) {
    int* values = new int[1];
    values[0] = 42;
    kogan::LinkedList<int> list(values, 1);
    delete[] values;

    ASSERT(list.get_last() == list.get(list.get_length() - 1));
    ASSERT(list.get_last() == 42);
}

TEST(get, linked_list_suite) {
    kogan::LinkedList<int> list;
    for (int i = 0; i < 10; ++i)
        list.append(i + 1);

    ASSERT(list.get(0) == 1);
    ASSERT(list.get(5) == 6);
    ASSERT(list.get(0) == list.get_first());
    ASSERT(list.get(list.get_length() - 1) == 10);
    ASSERT(list.get(list.get_length() - 1) == list.get_last());
}

TEST(get_single_item, linked_list_suite) {
    int* values = new int[1];
    values[0] = 42;
    kogan::LinkedList<int> list(values, 1);
    delete[] values;

    ASSERT(list.get(0) == 42);
    ASSERT(list.get(0) == list.get_first());
    ASSERT(list.get(0) == list.get_last());
}

TEST(get_negative_index_IndexOutOfRangeException, linked_list_suite) {
    kogan::LinkedList<int> list;
    for (int i = 0; i < 10; ++i)
        list.append(i + 1);

    bool indexOutOfRangeExceptionThrown = false;
    try {
        list.get(-1);
    } catch (kogan::IndexOutOfRangeException& e) {
        indexOutOfRangeExceptionThrown = true;
    }
    ASSERT(indexOutOfRangeExceptionThrown);
}

TEST(get_big_index_IndexOutOfRangeException, linked_list_suite) {
    kogan::LinkedList<int> list;
    for (int i = 0; i < 10; ++i)
        list.append(i + 1);

    bool indexOutOfRangeExceptionThrown = false;
    try {
        list.get(10);
    } catch (kogan::IndexOutOfRangeException& e) {
        indexOutOfRangeExceptionThrown = true;
    }
    ASSERT(indexOutOfRangeExceptionThrown);
}

TEST(get_subsequence, linked_list_suite) {
    kogan::LinkedList<int> list;
    for (int i = 0; i < 10; ++i)
        list.append(i + 1);

    kogan::LinkedList<int> sublist_35 = list.get_sublist(3, 5);
    ASSERT(sublist_35.get_length() == 3);
    ASSERT(sublist_35.get(0) == list.get(3));
    ASSERT(sublist_35.get(2) == list.get(5));
}

TEST(get_subsequence_max_bounds, linked_list_suite) {
    kogan::LinkedList<int> list;
    for (int i = 0; i < 10; ++i)
        list.append(i + 1);

    kogan::LinkedList<int> sublist_09 = list.get_sublist(0, 9);
    ASSERT(sublist_09.get_length() == 10);
    ASSERT(sublist_09.get(0) == list.get(0));
    ASSERT(sublist_09.get(9) == list.get(9));
}

TEST(get_subsequence_InvalidArgumentException, linked_list_suite) {
    kogan::LinkedList<int> list;
    for (int i = 0; i < 10; ++i)
        list.append(i + 1);

    bool invalidArgumentExceptionThrown = false;
    try {
        list.get_sublist(5, 3);
    } catch (kogan::InvalidArgumentException& e) {
        invalidArgumentExceptionThrown = true;
    }
    ASSERT(invalidArgumentExceptionThrown);
}

TEST(get_subsequence_negative_index_IndexOutOfRangeException, linked_list_suite) {
    kogan::LinkedList<int> list;
    for (int i = 0; i < 10; ++i)
        list.append(i + 1);

    bool indexOutOfRangeExceptionThrown = false;
    try {
        list.get_sublist(-1, 5);
    } catch (kogan::IndexOutOfRangeException& e) {
        indexOutOfRangeExceptionThrown = true;
    }
    ASSERT(indexOutOfRangeExceptionThrown);
}

TEST(get_subsequence_big_index_IndexOutOfRangeException, linked_list_suite) {
    kogan::LinkedList<int> list;
    for (int i = 0; i < 10; ++i)
        list.append(i + 1);

    bool indexOutOfRangeExceptionThrown = false;
    try {
        list.get_sublist(3, 10);
    } catch (kogan::IndexOutOfRangeException& e) {
        indexOutOfRangeExceptionThrown = true;
    }
    ASSERT(indexOutOfRangeExceptionThrown);
}

TEST(get_length, linked_list_suite) {
    kogan::LinkedList<int> list;
    for (int i = 0; i < 10; ++i)
        list.append(i + 1);

    ASSERT(list.get_length() == 10);

    kogan::LinkedList<int> list_empty;
    ASSERT(list_empty.get_length() == 0);
}

TEST(set, linked_list_suite) {
    kogan::LinkedList<int> list;
    for (int i = 0; i < 10; ++i)
        list.append(i + 1);

    for (int i = 0; i < 10; ++i)
        list.set(i, 10 - i);

    ASSERT(list.get(0) == 10);
    ASSERT(list.get(9) == 1);

    list.set(0, -34);
    ASSERT(list.get(0) == -34);
}

TEST(set_negative_index_IndexOutOfRangeException, linked_list_suite) {
    kogan::LinkedList<int> list;
    for (int i = 0; i < 10; ++i)
        list.append(i + 1);

    bool indexOutOfRangeExceptionThrown = false;
    try {
        list.set(-1, 0);
    } catch (kogan::IndexOutOfRangeException& e) {
        indexOutOfRangeExceptionThrown = true;
    }
    ASSERT(indexOutOfRangeExceptionThrown);
}

TEST(set_big_index_IndexOutOfRangeException, linked_list_suite) {
    kogan::LinkedList<int> list;
    for (int i = 0; i < 10; ++i)
        list.append(i + 1);

    bool indexOutOfRangeExceptionThrown = false;
    try {
        list.set(10, 0);
    } catch (kogan::IndexOutOfRangeException& e) {
        indexOutOfRangeExceptionThrown = true;
    }
    ASSERT(indexOutOfRangeExceptionThrown);
}

TEST(append, linked_list_suite) {
    kogan::LinkedList<int> list;
    for (int i = 0; i < 10; ++i)
        list.append(i + 1);

    ASSERT(list.get_length() == 10);
    ASSERT(list.get(0) == 1);
    ASSERT(list.get(4) == 5);
    ASSERT(list.get(9) == 10);

    list.append(-72);
    ASSERT(list.get_length() == 11);
    ASSERT(list.get(0) == 1);
    ASSERT(list.get(4) == 5);
    ASSERT(list.get(9) == 10);
    ASSERT(list.get(10) == -72);
}

TEST(prepend, linked_list_suite) {
    kogan::LinkedList<int> list;
    for (int i = 0; i < 10; ++i)
        list.prepend(i + 1);

    ASSERT(list.get_length() == 10);
    ASSERT(list.get(0) == 10);
    ASSERT(list.get(4) == 6);
    ASSERT(list.get(9) == 1);

    list.prepend(-72);
    ASSERT(list.get_length() == 11);
    ASSERT(list.get(1) == 10);
    ASSERT(list.get(5) == 6);
    ASSERT(list.get(10) == 1);
    ASSERT(list.get(0) == -72);
}

TEST(insert, linked_list_suite) {
    kogan::LinkedList<int> list;
    for (int i = 0; i < 10; ++i)
        list.append(i + 1);

    list.insert(0, 0);
    ASSERT(list.get(0) == 0);

    list.insert(11, 11);
    ASSERT(list.get(11) == 11);

    list.insert(5, -42);
    ASSERT(list.get(5) == -42);
    ASSERT(list.get(4) == 4);
    ASSERT(list.get(6) == 5);
}

TEST(insert_negative_index_IndexOutOfRangeException, linked_list_suite) {
    kogan::LinkedList<int> list;
    for (int i = 0; i < 10; ++i)
        list.append(i + 1);

    bool indexOutOfRangeExceptionThrown = false;
    try {
        list.insert(-1, 0);
    } catch (kogan::IndexOutOfRangeException& e) {
        indexOutOfRangeExceptionThrown = true;
    }
    ASSERT(indexOutOfRangeExceptionThrown);
}

TEST(insert_big_index_IndexOutOfRangeException, linked_list_suite) {
    kogan::LinkedList<int> list;
    for (int i = 0; i < 10; ++i)
        list.append(i + 1);

    bool indexOutOfRangeExceptionThrown = false;
    try {
        list.insert(11, 0);
    } catch (kogan::IndexOutOfRangeException& e) {
        indexOutOfRangeExceptionThrown = true;
    }
    ASSERT(indexOutOfRangeExceptionThrown);
}

TEST(concat, linked_list_suite) {
    kogan::LinkedList<int> list1;
    kogan::LinkedList<int> list2;
    for (int i = 0; i < 10; ++i) {
        list1.append(i + 1);
        list2.append(i + 11);
    }

    kogan::LinkedList<int> con12 = list1.concat(list2);
    ASSERT(con12.get_length() == list1.get_length() + list2.get_length());
    ASSERT(con12.get_length() == 20);
    ASSERT(con12.get(0) == 1);
    ASSERT(con12.get(9) == 10);
    ASSERT(con12.get(10) == 11);
    ASSERT(con12.get(19) == 20);
}

TEST(concat_empty_tail, linked_list_suite) {
    kogan::LinkedList<int> list1;
    for (int i = 0; i < 10; ++i)
        list1.append(i + 1);

    kogan::LinkedList<int> list_empty;
    kogan::LinkedList<int> con1e = list1.concat(list_empty);
    ASSERT(con1e.get_length() == list1.get_length() + list_empty.get_length());
    ASSERT(con1e.get_length() == 10);
    ASSERT(con1e.get(0) == 1);
    ASSERT(con1e.get(9) == 10);
}

TEST(concat_empty_head, linked_list_suite) {
    kogan::LinkedList<int> list2;
    for (int i = 0; i < 10; ++i)
        list2.append(i + 11);

    kogan::LinkedList<int> list_empty;
    kogan::LinkedList<int> cone2 = list_empty.concat(list2);
    ASSERT(cone2.get_length() == list_empty.get_length() + list2.get_length());
    ASSERT(cone2.get_length() == 10);
    ASSERT(cone2.get(0) == 11);
    ASSERT(cone2.get(9) == 20);
}

TEST(clear, linked_list_suite) {
    kogan::LinkedList<int> list;
    for (int i = 0; i < 10; ++i)
        list.append(i + 1);

    list.clear();
    ASSERT(list.get_length() == 0);
}

TEST(clear_empty, linked_list_suite) {
    kogan::LinkedList<int> list;

    list.clear();
    ASSERT(list.get_length() == 0);
}

TEST(remove, linked_list_suite) {
    kogan::LinkedList<int> list;
    for (int i = 0; i < 10; ++i)
        list.append(i + 1);

    list.remove(5);
    ASSERT(list.get_length() == 9);
    ASSERT(list.get(0) == 1);
    ASSERT(list.get(4) == 5);
    ASSERT(list.get(5) == 7);
    ASSERT(list.get(8) == 10);
}

TEST(remove_first, linked_list_suite) {
    kogan::LinkedList<int> list;
    for (int i = 0; i < 10; ++i)
        list.append(i + 1);

    list.remove(0);
    ASSERT(list.get_length() == 9);
    ASSERT(list.get(0) == 2);
    ASSERT(list.get(8) == 10);
}

TEST(remove_last, linked_list_suite) {
    kogan::LinkedList<int> list;
    for (int i = 0; i < 10; ++i)
        list.append(i + 1);

    list.remove(9);
    ASSERT(list.get_length() == 9);
    ASSERT(list.get(0) == 1);
    ASSERT(list.get(8) == 9);
}

TEST(remove_single_item, linked_list_suite) {
    kogan::LinkedList<int> list;
    list.append(42);
    list.remove(0);
    ASSERT(list.get_length() == 0);
}

TEST(remove_big_index_IndexOutOfRangeException, linked_list_suite) {
    kogan::LinkedList<int> list;
    for (int i = 0; i < 10; ++i)
        list.append(i + 1);

    bool indexOutOfRangeExceptionThrown = false;
    try {
        list.remove(10);
    } catch (kogan::IndexOutOfRangeException& e) {
        indexOutOfRangeExceptionThrown = true;
    }
    ASSERT(indexOutOfRangeExceptionThrown);
}

TEST(remove_negative_index_IndexOutOfRangeException, linked_list_suite) {
    kogan::LinkedList<int> list;
    for (int i = 0; i < 10; ++i)
        list.append(i + 1);

    bool indexOutOfRangeExceptionThrown = false;
    try {
        list.remove(-1);
    } catch (kogan::IndexOutOfRangeException& e) {
        indexOutOfRangeExceptionThrown = true;
    }
    ASSERT(indexOutOfRangeExceptionThrown);
}

TEST(remove_empty_IndexOutOfRangeException, linked_list_suite) {
    kogan::LinkedList<int> list;

    bool indexOutOfRangeExceptionThrown = false;
    try {
        list.remove(0);
    } catch (kogan::IndexOutOfRangeException& e) {
        indexOutOfRangeExceptionThrown = true;
    }
    ASSERT(indexOutOfRangeExceptionThrown);
}


kogan::TestSuite get_linked_list_suite() {
    return linked_list_suite;
}
