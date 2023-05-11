//
// Created by Gregory Kogan on 07.05.2023.
//

#ifndef SEQUENCE_LIB_MENUS_HPP
#define SEQUENCE_LIB_MENUS_HPP

#include <limits>
#include <iostream>
#include "../sequences/ArraySequence.hpp"
#include "../sequences/LinkedListSequence.hpp"
#include "../IO/colored_logs.hpp"

enum action {
    EXIT,
    SELECT_ACTION,
    INPUT,
    SET,
    APPEND,
    PREPEND,
    INSERT,
    CONCATENATE,
    SUBSEQUENCE,
    REMOVE,
    CLEAR,
    LENGTH
};

action select_action_menu(kogan::ArraySequence<int>* array_seq, kogan::LinkedListSequence<int>* linked_list_seq);
void input_menu(kogan::ArraySequence<int>* array_seq, kogan::LinkedListSequence<int>* linked_list_seq);
void set_menu(kogan::ArraySequence<int>* array_seq, kogan::LinkedListSequence<int>* linked_list_seq);
void append_menu(kogan::ArraySequence<int>* array_seq, kogan::LinkedListSequence<int>* linked_list_seq);
void prepend_menu(kogan::ArraySequence<int>* array_seq, kogan::LinkedListSequence<int>* linked_list_seq);
void insert_menu(kogan::ArraySequence<int>* array_seq, kogan::LinkedListSequence<int>* linked_list_seq);
void concatenate_menu(kogan::ArraySequence<int>* array_seq, kogan::LinkedListSequence<int>* linked_list_seq);
void subsequence_menu(kogan::ArraySequence<int>* array_seq, kogan::LinkedListSequence<int>* linked_list_seq);
void remove_menu(kogan::ArraySequence<int>* array_seq, kogan::LinkedListSequence<int>* linked_list_seq);
void clear_menu(kogan::ArraySequence<int>* array_seq, kogan::LinkedListSequence<int>* linked_list_seq);
void length_menu(kogan::ArraySequence<int>* array_seq, kogan::LinkedListSequence<int>* linked_list_seq);

#endif //SEQUENCE_LIB_MENUS_HPP
