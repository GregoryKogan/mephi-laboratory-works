//
// Created by Gregory Kogan on 07.05.2023.
//

#include "menus.h"


void panic_if_invalid_input(std::string argument_name) {
    if (!std::cin.good()) {
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        throw kogan::InvalidArgumentException(std::move(argument_name));
    }
}

action select_action_menu(kogan::ArraySequence<int>* array_seq, kogan::LinkedListSequence<int>* linked_list_seq) {
    std::cout << "ArraySequence:      " << *array_seq << std::endl;
    std::cout << "LinkedListSequence: " << *linked_list_seq << std::endl << std::endl;

    log_blue("Select action: "); std::cout << std::endl;
    std::cout << "1 - exit program" << std::endl;
    std::cout << "2 - input" << std::endl;
    std::cout << "3 - set" << std::endl;
    std::cout << "4 - append" << std::endl;
    std::cout << "5 - prepend" << std::endl;
    std::cout << "6 - insert" << std::endl;
    std::cout << "7 - concatenate" << std::endl;
    std::cout << "8 - get subsequence" << std::endl;
    std::cout << "9 - remove" << std::endl;
    std::cout << "10 - clear" << std::endl;
    std::cout << "11 - get length" << std::endl;

    int user_input;
    std::cout << ">>> ";
    std::cin >> user_input;
    panic_if_invalid_input("action");

    switch (user_input) {
        case 1:
            return EXIT;
        case 2:
            return INPUT;
        case 3:
            return SET;
        case 4:
            return APPEND;
        case 5:
            return PREPEND;
        case 6:
            return INSERT;
        case 7:
            return CONCATENATE;
        case 8:
            return SUBSEQUENCE;
        case 9:
            return REMOVE;
        case 10:
            return CLEAR;
        case 11:
            return LENGTH;
        default:
            throw kogan::InvalidArgumentException("action");
    }
}

kogan::Sequence<int>* select_sequence_menu(
        kogan::ArraySequence<int>* array_seq,
        kogan::LinkedListSequence<int>* linked_list_seq,
        int* selected_type = nullptr
) {
    log_blue("Select sequence: "); std::cout << std::endl;
    std::cout << "1 - ArraySequence" << std::endl;
    std::cout << "2 - LinkedListSequence" << std::endl;

    std::cout << ">>> ";
    int user_input; std::cin >> user_input;
    panic_if_invalid_input("sequence");

    const int ARRAY = 1;
    const int LIST = 2;

    switch (user_input) {
        case 1:
            if (selected_type != nullptr)
                *selected_type = ARRAY;
            return array_seq;
        case 2:
            if (selected_type != nullptr)
                *selected_type = LIST;
            return linked_list_seq;
        default:
            throw kogan::InvalidArgumentException("sequence");
    }
}

void input_menu(kogan::ArraySequence<int>* array_seq, kogan::LinkedListSequence<int>* linked_list_seq) {
    log_blue("Input sequence"); std::cout << std::endl;
    kogan::Sequence<int>* seq = select_sequence_menu(array_seq, linked_list_seq);

    std::cout << "Sequence length: ";
    int seq_length; std::cin >> seq_length;
    panic_if_invalid_input("length");
    if (seq_length < 0)
        throw kogan::InvalidArgumentException("length");

    if (seq_length == 0) return;

    std::cout << "Input sequence values: " << std::endl;
    seq->clear();
    for (int i = 0; i < seq_length; ++i) {
        int val; std::cin >> val;
        panic_if_invalid_input("sequence value");
        seq->append(val);
    }
}

void set_menu(kogan::ArraySequence<int>* array_seq, kogan::LinkedListSequence<int>* linked_list_seq) {
    log_blue("Set sequence's value"); std::cout << std::endl;
    kogan::Sequence<int>* seq = select_sequence_menu(array_seq, linked_list_seq);

    std::cout << "index: ";
    int index; std::cin >> index;
    panic_if_invalid_input("index");

    std::cout << "value: ";
    int value; std::cin >> value;
    panic_if_invalid_input("value");

    (*seq)[index] = value;
}

void append_menu(kogan::ArraySequence<int>* array_seq, kogan::LinkedListSequence<int>* linked_list_seq) {
    log_blue("Append value"); std::cout << std::endl;
    kogan::Sequence<int>* seq = select_sequence_menu(array_seq, linked_list_seq);

    std::cout << "value: ";
    int value; std::cin >> value;
    panic_if_invalid_input("value");

    seq->append(value);
}

void prepend_menu(kogan::ArraySequence<int>* array_seq, kogan::LinkedListSequence<int>* linked_list_seq) {
    log_blue("Prepend value"); std::cout << std::endl;
    kogan::Sequence<int>* seq = select_sequence_menu(array_seq, linked_list_seq);

    std::cout << "value: ";
    int value; std::cin >> value;
    panic_if_invalid_input("value");

    seq->prepend(value);
}

void insert_menu(kogan::ArraySequence<int>* array_seq, kogan::LinkedListSequence<int>* linked_list_seq) {
    log_blue("Insert value"); std::cout << std::endl;
    kogan::Sequence<int>* seq = select_sequence_menu(array_seq, linked_list_seq);

    std::cout << "index: ";
    int index; std::cin >> index;
    panic_if_invalid_input("index");

    std::cout << "value: ";
    int value; std::cin >> value;
    panic_if_invalid_input("value");

    seq->insert(index, value);
}

void concatenate_menu(kogan::ArraySequence<int>* array_seq, kogan::LinkedListSequence<int>* linked_list_seq) {
    log_blue("Concatenate sequences"); std::cout << std::endl;
    int selected_type;
    kogan::Sequence<int>* seq = select_sequence_menu(array_seq, linked_list_seq, &selected_type);

    std::cout << "Second sequence's length: ";
    int seq_length; std::cin >> seq_length;
    panic_if_invalid_input("length");
    if (seq_length < 0)
        throw kogan::InvalidArgumentException("length");

    kogan::ArraySequence<int> second_arr_seq;
    kogan::LinkedListSequence<int> second_list_seq;

    kogan::Sequence<int>* second_seq_ptr;
    const int ARRAY = 1;
    if (selected_type == ARRAY)
        second_seq_ptr = &second_arr_seq;
    else
        second_seq_ptr = &second_list_seq;

    if (seq_length > 0) {
        std::cout << "Input second sequence values: " << std::endl;
        for (int i = 0; i < seq_length; ++i) {
            int val; std::cin >> val;
            panic_if_invalid_input("sequence value");
            second_seq_ptr->append(val);
        }
    }

    kogan::Sequence<int>* concatenation = seq->concat(second_seq_ptr);

    std::cout << "Concatenation: " << std::endl << *concatenation << std::endl << std::endl;
    delete concatenation;
}

void subsequence_menu(kogan::ArraySequence<int>* array_seq, kogan::LinkedListSequence<int>* linked_list_seq) {
    log_blue("Get subsequence"); std::cout << std::endl;
    kogan::Sequence<int>* seq = select_sequence_menu(array_seq, linked_list_seq);

    std::cout << "start index: ";
    int start_index; std::cin >> start_index;
    panic_if_invalid_input("start index");

    std::cout << "end index: ";
    int end_index; std::cin >> end_index;
    panic_if_invalid_input("end index");

    kogan::Sequence<int>* sub_seq = seq->get_subsequence(start_index, end_index);
    std::cout << "Subsequence: " << std::endl << *sub_seq << std::endl << std::endl;
    delete sub_seq;
}

void remove_menu(kogan::ArraySequence<int>* array_seq, kogan::LinkedListSequence<int>* linked_list_seq) {
    log_blue("Remove value"); std::cout << std::endl;
    kogan::Sequence<int>* seq = select_sequence_menu(array_seq, linked_list_seq);

    std::cout << "index: ";
    int index; std::cin >> index;
    panic_if_invalid_input("index");

    seq->remove(index);
}

void clear_menu(kogan::ArraySequence<int>* array_seq, kogan::LinkedListSequence<int>* linked_list_seq) {
    log_blue("Clear sequence"); std::cout << std::endl;
    kogan::Sequence<int>* seq = select_sequence_menu(array_seq, linked_list_seq);

    seq->clear();
}

void length_menu(kogan::ArraySequence<int>* array_seq, kogan::LinkedListSequence<int>* linked_list_seq) {
    log_blue("Get length"); std::cout << std::endl;
    kogan::Sequence<int>* seq = select_sequence_menu(array_seq, linked_list_seq);

    std::cout << "Length: " << seq->get_length() << std::endl << std::endl;
}
