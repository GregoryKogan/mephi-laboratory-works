//
// Created by Gregory Kogan on 07.05.2023.
//

#include "LinkedListSequence_tests.h"


kogan::TestSuite linked_list_sequence_suite("LinkedListSequence");


TEST(array_constructor, linked_list_sequence_suite) {
    int* values = new int[10];
    for (int i = 0; i < 10; ++i)
        values[i] = i + 1;

    kogan::LinkedListSequence<int> seq(values, 10);
    delete[] values;

    ASSERT(seq.get_length() == 10);
    ASSERT(seq[0] == 1);
    ASSERT(seq[2] == 3);
    ASSERT(seq[9] == 10);
}

TEST(empty_constructor, linked_list_sequence_suite) {
    kogan::LinkedListSequence<int> seq;

    ASSERT(seq.get_length() == 0);
}

TEST(sequence_constructor, linked_list_sequence_suite) {
    int* values = new int[10];
    for (int i = 0; i < 10; ++i)
        values[i] = i + 1;

    kogan::LinkedListSequence<int> init_seq(values, 10);
    kogan::LinkedListSequence<int> seq(init_seq);
    delete[] values;

    ASSERT(seq.get_length() == init_seq.get_length());
    ASSERT(seq.get_length() == 10);
    ASSERT(seq[0] == 1);
    ASSERT(seq[2] == 3);
    ASSERT(seq[9] == 10);
    ASSERT(seq[0] == init_seq[0]);
    ASSERT(seq[2] == init_seq[2]);
    ASSERT(seq[9] == init_seq[9]);
}

TEST(get_first, linked_list_sequence_suite) {
    kogan::LinkedListSequence<int> seq;
    for (int i = 0; i < 10; ++i)
        seq.append(i + 1);

    ASSERT(seq.get_first() == seq[0]);
    ASSERT(seq.get_first() == 1);
}

TEST(get_first_single_item, linked_list_sequence_suite) {
    kogan::LinkedListSequence<int> seq;
    seq.append(1);

    ASSERT(seq.get_first() == seq[0]);
    ASSERT(seq.get_first() == 1);
}

TEST(get_last, linked_list_sequence_suite) {
    kogan::LinkedListSequence<int> seq;
    for (int i = 0; i < 10; ++i)
        seq.append(i + 1);

    ASSERT(seq.get_last() == seq[seq.get_length() - 1]);
    ASSERT(seq.get_last() == 10);
}

TEST(get_last_single_item, linked_list_sequence_suite) {
    kogan::LinkedListSequence<int> seq;
    seq.append(1);

    ASSERT(seq.get_last() == seq[seq.get_length() - 1]);
    ASSERT(seq.get_last() == 1);
}

TEST(get, linked_list_sequence_suite) {
    kogan::LinkedListSequence<int> seq;
    for (int i = 0; i < 10; ++i)
        seq.append(i + 1);

    ASSERT(seq.get(0) == 1);
    ASSERT(seq.get(0) == seq[0]);
    ASSERT(seq.get(0) == seq.get_first());
    ASSERT(seq.get(seq.get_length() - 1) == 10);
    ASSERT(seq.get(seq.get_length() - 1) == seq[seq.get_length() - 1]);
    ASSERT(seq.get(seq.get_length() - 1) == seq.get_last());
}

TEST(get_single_item, linked_list_sequence_suite) {
    kogan::LinkedListSequence<int> seq;
    seq.append(1);

    ASSERT(seq.get(0) == 1);
    ASSERT(seq.get(0) == seq[0]);
    ASSERT(seq.get(0) == seq.get_first());
    ASSERT(seq.get(0) == seq.get_last());
}

TEST(get_negative_index_IndexOutOfRangeException, linked_list_sequence_suite) {
    kogan::LinkedListSequence<int> seq;
    for (int i = 0; i < 10; ++i)
        seq.append(i + 1);

    bool indexOutOfRangeExceptionThrown = false;
    try {
        seq.get(-1);
    } catch (kogan::IndexOutOfRangeException& e) {
        indexOutOfRangeExceptionThrown = true;
    }
    ASSERT(indexOutOfRangeExceptionThrown);
}

TEST(get_big_index_IndexOutOfRangeException, linked_list_sequence_suite) {
    kogan::LinkedListSequence<int> seq;
    for (int i = 0; i < 10; ++i)
        seq.append(i + 1);

    bool indexOutOfRangeExceptionThrown = false;
    try {
        seq.get(10);
    } catch (kogan::IndexOutOfRangeException& e) {
        indexOutOfRangeExceptionThrown = true;
    }
    ASSERT(indexOutOfRangeExceptionThrown);
}

TEST(get_subsequence, linked_list_sequence_suite) {
    kogan::LinkedListSequence<int> seq;
    for (int i = 0; i < 10; ++i)
        seq.append(i + 1);

    kogan::Sequence<int>* sub_seq_35 = seq.get_subsequence(3, 5);
    ASSERT(sub_seq_35->get_length() == 3);
    ASSERT((*sub_seq_35)[0] == seq[3]);
    ASSERT((*sub_seq_35)[2] == seq[5]);
    delete sub_seq_35;
}

TEST(get_subsequence_max_bounds, linked_list_sequence_suite) {
    kogan::LinkedListSequence<int> seq;
    for (int i = 0; i < 10; ++i)
        seq.append(i + 1);

    kogan::Sequence<int>* sub_seq_09 = seq.get_subsequence(0, 9);
    ASSERT(sub_seq_09->get_length() == 10);
    ASSERT((*sub_seq_09)[0] == seq[0]);
    ASSERT((*sub_seq_09)[9] == seq[9]);
    delete sub_seq_09;
}

TEST(get_subsequence_InvalidArgumentException, linked_list_sequence_suite) {
    kogan::LinkedListSequence<int> seq;
    for (int i = 0; i < 10; ++i)
        seq.append(i + 1);

    bool invalidArgumentExceptionThrown = false;
    try {
        seq.get_subsequence(5, 3);
    } catch (kogan::InvalidArgumentException& e) {
        invalidArgumentExceptionThrown = true;
    }
    ASSERT(invalidArgumentExceptionThrown);
}

TEST(get_subsequence_negative_index_IndexOutOfRangeException, linked_list_sequence_suite) {
    kogan::LinkedListSequence<int> seq;
    for (int i = 0; i < 10; ++i)
        seq.append(i + 1);

    bool indexOutOfRangeExceptionThrown = false;
    try {
        seq.get_subsequence(-1, 5);
    } catch (kogan::IndexOutOfRangeException& e) {
        indexOutOfRangeExceptionThrown = true;
    }
    ASSERT(indexOutOfRangeExceptionThrown);
}

TEST(get_subsequence_big_index_IndexOutOfRangeException, linked_list_sequence_suite) {
    kogan::LinkedListSequence<int> seq;
    for (int i = 0; i < 10; ++i)
        seq.append(i + 1);

    bool indexOutOfRangeExceptionThrown = false;
    try {
        seq.get_subsequence(3, 10);
    } catch (kogan::IndexOutOfRangeException& e) {
        indexOutOfRangeExceptionThrown = true;
    }
    ASSERT(indexOutOfRangeExceptionThrown);
}

TEST(get_length, linked_list_sequence_suite) {
    kogan::LinkedListSequence<int> seq;
    for (int i = 0; i < 10; ++i)
        seq.append(i + 1);

    ASSERT(seq.get_length() == 10);

    kogan::LinkedListSequence<int> seq_empty;
    ASSERT(seq_empty.get_length() == 0);
}

TEST(set, linked_list_sequence_suite) {
    kogan::LinkedListSequence<int> seq;
    for (int i = 0; i < 10; ++i)
        seq.append(i + 1);

    for (int i = 0; i < 10; ++i)
        seq.set(i, 10 - i);

    ASSERT(seq[0] == 10);
    ASSERT(seq[9] == 1);

    seq.set(0, -34);
    ASSERT(seq[0] == -34);
}

TEST(set_negative_index_IndexOutOfRangeException, linked_list_sequence_suite) {
    kogan::LinkedListSequence<int> seq;
    for (int i = 0; i < 10; ++i)
        seq.append(i + 1);

    bool indexOutOfRangeExceptionThrown = false;
    try {
        seq.set(-1, 0);
    } catch (kogan::IndexOutOfRangeException& e) {
        indexOutOfRangeExceptionThrown = true;
    }
    ASSERT(indexOutOfRangeExceptionThrown);
}

TEST(set_big_index_IndexOutOfRangeException, linked_list_sequence_suite) {
    kogan::LinkedListSequence<int> seq;
    for (int i = 0; i < 10; ++i)
        seq.append(i + 1);

    bool indexOutOfRangeExceptionThrown = false;
    try {
        seq.set(10, 0);
    } catch (kogan::IndexOutOfRangeException& e) {
        indexOutOfRangeExceptionThrown = true;
    }
    ASSERT(indexOutOfRangeExceptionThrown);
}

TEST(append, linked_list_sequence_suite) {
    kogan::LinkedListSequence<int> seq;
    for (int i = 0; i < 10; ++i)
        seq.append(i + 1);

    ASSERT(seq.get_length() == 10);
    ASSERT(seq[0] == 1);
    ASSERT(seq[4] == 5);
    ASSERT(seq[9] == 10);

    seq.append(-72);
    ASSERT(seq.get_length() == 11);
    ASSERT(seq[0] == 1);
    ASSERT(seq[4] == 5);
    ASSERT(seq[9] == 10);
    ASSERT(seq[10] == -72);
}

TEST(prepend, linked_list_sequence_suite) {
    kogan::LinkedListSequence<int> seq;
    for (int i = 0; i < 10; ++i)
        seq.prepend(i + 1);

    ASSERT(seq.get_length() == 10);
    ASSERT(seq[0] == 10);
    ASSERT(seq[4] == 6);
    ASSERT(seq[9] == 1);

    seq.prepend(-72);
    ASSERT(seq.get_length() == 11);
    ASSERT(seq[1] == 10);
    ASSERT(seq[5] == 6);
    ASSERT(seq[10] == 1);
    ASSERT(seq[0] == -72);
}

TEST(insert, linked_list_sequence_suite) {
    kogan::LinkedListSequence<int> seq;
    for (int i = 0; i < 10; ++i)
        seq.append(i + 1);

    seq.insert(0, 0);
    ASSERT(seq[0] == 0);

    seq.insert(11, 11);
    ASSERT(seq[11] == 11);

    seq.insert(5, -42);
    ASSERT(seq[5] == -42);
    ASSERT(seq[4] == 4);
    ASSERT(seq[6] == 5);
}

TEST(insert_negative_index_IndexOutOfRangeException, linked_list_sequence_suite) {
    kogan::LinkedListSequence<int> seq;
    for (int i = 0; i < 10; ++i)
        seq.append(i + 1);

    bool indexOutOfRangeExceptionThrown = false;
    try {
        seq.insert(-1, 0);
    } catch (kogan::IndexOutOfRangeException& e) {
        indexOutOfRangeExceptionThrown = true;
    }
    ASSERT(indexOutOfRangeExceptionThrown);
}

TEST(insert_big_index_IndexOutOfRangeException, linked_list_sequence_suite) {
    kogan::LinkedListSequence<int> seq;
    for (int i = 0; i < 10; ++i)
        seq.append(i + 1);

    bool indexOutOfRangeExceptionThrown = false;
    try {
        seq.insert(11, 0);
    } catch (kogan::IndexOutOfRangeException& e) {
        indexOutOfRangeExceptionThrown = true;
    }
    ASSERT(indexOutOfRangeExceptionThrown);
}

TEST(concat, linked_list_sequence_suite) {
    kogan::LinkedListSequence<int> seq1;
    kogan::LinkedListSequence<int> seq2;
    for (int i = 0; i < 10; ++i) {
        seq1.append(i + 1);
        seq2.append(i + 11);
    }

    kogan::Sequence<int>* con12 = seq1.concat(&seq2);
    ASSERT(con12->get_length() == seq1.get_length() + seq2.get_length());
    ASSERT(con12->get_length() == 20);
    ASSERT((*con12)[0] == 1);
    ASSERT((*con12)[9] == 10);
    ASSERT((*con12)[10] == 11);
    ASSERT((*con12)[19] == 20);
    delete con12;
}

TEST(concat_empty_tail, linked_list_sequence_suite) {
    kogan::LinkedListSequence<int> seq1;
    kogan::LinkedListSequence<int> seq2;
    for (int i = 0; i < 10; ++i) {
        seq1.append(i + 1);
        seq2.append(i + 11);
    }

    kogan::LinkedListSequence<int> seq_empty;
    kogan::Sequence<int>* con1e = seq1.concat(&seq_empty);
    ASSERT(con1e->get_length() == seq1.get_length() + seq_empty.get_length());
    ASSERT(con1e->get_length() == 10);
    ASSERT((*con1e)[0] == 1);
    ASSERT((*con1e)[9] == 10);
    delete con1e;
}

TEST(concat_empty_head, linked_list_sequence_suite) {
    kogan::LinkedListSequence<int> seq1;
    kogan::LinkedListSequence<int> seq2;
    for (int i = 0; i < 10; ++i) {
        seq1.append(i + 1);
        seq2.append(i + 11);
    }

    kogan::LinkedListSequence<int> seq_empty;
    kogan::Sequence<int>* cone2 = seq_empty.concat(&seq2);
    ASSERT(cone2->get_length() == seq_empty.get_length() + seq2.get_length());
    ASSERT(cone2->get_length() == 10);
    ASSERT((*cone2)[0] == 11);
    ASSERT((*cone2)[9] == 20);
    delete cone2;
}

TEST(clear, linked_list_sequence_suite) {
    kogan::LinkedListSequence<int> seq;
    for (int i = 0; i < 10; ++i)
        seq.append(i + 1);

    seq.clear();
    ASSERT(seq.get_length() == 0);
}

TEST(clear_empty, linked_list_sequence_suite) {
    kogan::LinkedListSequence<int> seq;

    seq.clear();
    ASSERT(seq.get_length() == 0);
}

kogan::TestSuite get_linked_list_sequence_suite() {
    return linked_list_sequence_suite;
}
