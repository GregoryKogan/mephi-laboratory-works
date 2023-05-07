//
// Created by Gregory Kogan on 07.05.2023.
//

#include "menus.h"


action select_action_menu(kogan::ArraySequence<int>* array_seq, kogan::LinkedListSequence<int>* linked_list_seq) {
    std::cout << "ArraySequence:      " << *array_seq << std::endl;
    std::cout << "LinkedListSequence: " << *linked_list_seq << std::endl;

    std::cout << "Select action: " << std::endl;
    std::cout << "1 - exit program" << std::endl;
    std::cout << "2 - input" << std::endl;
    std::cout << "3 - set" << std::endl;
    std::cout << "4 - append" << std::endl;
    std::cout << "5 - prepend" << std::endl;
    std::cout << "6 - insert" << std::endl;
    std::cout << "7 - concatenate" << std::endl;
    std::cout << "8 - get subsequence" << std::endl;
    std::cout << "9 - get length" << std::endl;

    int user_input;
    std::cout << ">>> ";
    std::cin >> user_input;

    if (!std::cin.good()) {
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        user_input = 0;
    }

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
            return LENGTH;
        default:
            throw kogan::InvalidArgumentException("action");
    }
}

kogan::Sequence<int>* select_sequence_menu(kogan::ArraySequence<int>* array_seq, kogan::LinkedListSequence<int>* linked_list_seq) {
    std::cout << "Select sequence: " << std::endl;
    std::cout << "1 - ArraySequence" << std::endl;
    std::cout << "2 - LinkedListSequence" << std::endl;

    int user_input;
    std::cout << ">>> ";
    std::cin >> user_input;

    if (!std::cin.good()) {
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        user_input = 0;
    }

    switch (user_input) {
        case 1:
            return array_seq;
        case 2:
            return linked_list_seq;
        default:
            throw kogan::InvalidArgumentException("sequence");
    }
}

void input_menu(kogan::ArraySequence<int>* array_seq, kogan::LinkedListSequence<int>* linked_list_seq) {
    std::cout << "Input sequence" << std::endl;
    kogan::Sequence<int>* seq = select_sequence_menu(array_seq, linked_list_seq);

    std::cout << "Sequence length: ";
    int seq_length; std::cin >> seq_length;
    if (!std::cin.good() || seq_length < 0) {
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        throw kogan::InvalidArgumentException("length");
    }

    if (seq_length == 0) return;

    std::cout << "Input sequence values: " << std::endl;
    seq->clear();
    for (int i = 0; i < seq_length; ++i) {
        int val; std::cin >> val;
        if (!std::cin.good()) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            throw kogan::InvalidArgumentException("sequence value");
        }

        seq->append(val);
    }
}

void set_menu(kogan::ArraySequence<int>* array_seq, kogan::LinkedListSequence<int>* linked_list_seq) {
    std::cout << "Set sequence's value" << std::endl;
    kogan::Sequence<int>* seq = select_sequence_menu(array_seq, linked_list_seq);

    std::cout << "index: ";
    int index; std::cin >> index;
    if (!std::cin.good()) {
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        throw kogan::InvalidArgumentException("index");
    }

    std::cout << "value: ";
    int value; std::cin >> value;
    if (!std::cin.good()) {
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        throw kogan::InvalidArgumentException("value");
    }

    (*seq)[index] = value;
}

void append_menu(kogan::ArraySequence<int>* array_seq, kogan::LinkedListSequence<int>* linked_list_seq) {
    std::cout << "Append value" << std::endl;
    kogan::Sequence<int>* seq = select_sequence_menu(array_seq, linked_list_seq);

    std::cout << "value: ";
    int value; std::cin >> value;
    if (!std::cin.good()) {
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        throw kogan::InvalidArgumentException("value");
    }

    seq->append(value);
}
