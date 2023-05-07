//
// Created by Gregory Kogan on 07.05.2023.
//

#ifndef SEQUENCE_LIB_MENUS_H
#define SEQUENCE_LIB_MENUS_H

#include <limits>
#include <iostream>
#include "../sequences/ArraySequence.h"
#include "../sequences/LinkedListSequence.h"

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
    LENGTH
};

action select_action_menu(kogan::ArraySequence<int>* array_seq, kogan::LinkedListSequence<int>* linked_list_seq);
void input_menu(kogan::ArraySequence<int>* array_seq, kogan::LinkedListSequence<int>* linked_list_seq);
void set_menu(kogan::ArraySequence<int>* array_seq, kogan::LinkedListSequence<int>* linked_list_seq);
void append_menu(kogan::ArraySequence<int>* array_seq, kogan::LinkedListSequence<int>* linked_list_seq);

#endif //SEQUENCE_LIB_MENUS_H
