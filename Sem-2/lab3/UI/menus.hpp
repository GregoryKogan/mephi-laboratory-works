//
// Created by Gregory Kogan on 20.05.2023.
//

#ifndef LAB3_MENUS_HPP
#define LAB3_MENUS_HPP

#include <limits>
#include <IO/colored_logs.hpp>
#include "../containers/queue/queue.hpp"
#include "../containers/stack/stack.hpp"
#include "../containers/deque/deque.hpp"


struct QueueStackDeque {
    kogan::Queue<int>* queue;
    kogan::Stack<int>* stack;
    kogan::Deque<int>* deque;
};

enum action {
    EXIT,
    PUSH,
    POP,
    PUSH_FRONT,
    POP_FRONT,
    PUSH_BACK,
    POP_BACK,
    GET_SUBSEQUENCE,
    CONCAT,
};

enum container_type {
    QUEUE,
    STACK,
    DEQUE,
};

container_type select_container_menu(struct QueueStackDeque& containers);
action select_queue_action_menu();
action select_stack_action_menu();
action select_deque_action_menu();
void print_containers(struct QueueStackDeque& containers);

void push_queue_menu(kogan::Queue<int>* queue);
void push_stack_menu(kogan::Stack<int>* stack);
void pop_queue_menu(kogan::Queue<int>* queue);
void pop_stack_menu(kogan::Stack<int>* stack);
void push_front_deque_menu(kogan::Deque<int>* deque);
void pop_front_deque_menu(kogan::Deque<int>* deque);
void push_back_deque_menu(kogan::Deque<int>* deque);
void pop_back_deque_menu(kogan::Deque<int>* deque);
void get_subsequence_menu(kogan::BaseContainer<int>* container);
void concat_queue_menu(kogan::Queue<int>* queue);
void concat_stack_menu(kogan::Stack<int>* stack);
void concat_deque_menu(kogan::Deque<int>* deque);

void panic_if_invalid_input(std::string argument_name);

#endif //LAB3_MENUS_HPP
