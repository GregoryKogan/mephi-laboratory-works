//
// Created by Gregory Kogan on 20.05.2023.
//

#include "menus.hpp"


container_type select_container_menu(struct QueueStackDeque& containers) {
    for (int i = 0; i < 5; ++i) std::cout << std::endl;

    print_containers(containers); std::cout << std::endl;

    log_blue("Select container: "); std::cout << std::endl;
    std::cout << "1 - Queue" << std::endl;
    std::cout << "2 - Stack" << std::endl;
    std::cout << "3 - Deque" << std::endl;

    int user_input;
    std::cout << ">>> ";
    std::cin >> user_input;
    panic_if_invalid_input("container");

    switch (user_input) {
        case 1:
            return QUEUE;
        case 2:
            return STACK;
        case 3:
            return DEQUE;
        default:
            throw kogan::InvalidArgumentException("container");
    }
}


action select_queue_action_menu() {
    log_blue("Select QUEUE action: "); std::cout << std::endl;
    std::cout << "1 - exit program" << std::endl;
    std::cout << "2 - push" << std::endl;
    std::cout << "3 - pop" << std::endl;
    std::cout << "4 - get subsequence" << std::endl;
    std::cout << "5 - concat" << std::endl;

    int user_input;
    std::cout << ">>> ";
    std::cin >> user_input;
    panic_if_invalid_input("action");

    switch (user_input) {
        case 1:
            return EXIT;
        case 2:
            return PUSH;
        case 3:
            return POP;
        case 4:
            return GET_SUBSEQUENCE;
        case 5:
            return CONCAT;
        default:
            throw kogan::InvalidArgumentException("action");
    }
}


action select_stack_action_menu() {
    log_blue("Select STACK action: "); std::cout << std::endl;
    std::cout << "1 - exit program" << std::endl;
    std::cout << "2 - push" << std::endl;
    std::cout << "3 - pop" << std::endl;
    std::cout << "4 - get subsequence" << std::endl;
    std::cout << "5 - concat" << std::endl;

    int user_input;
    std::cout << ">>> ";
    std::cin >> user_input;
    panic_if_invalid_input("action");

    switch (user_input) {
        case 1:
            return EXIT;
        case 2:
            return PUSH;
        case 3:
            return POP;
        case 4:
            return GET_SUBSEQUENCE;
        case 5:
            return CONCAT;
        default:
            throw kogan::InvalidArgumentException("action");
    }
}


action select_deque_action_menu() {
    log_blue("Select DEQUE action: "); std::cout << std::endl;
    std::cout << "1 - exit program" << std::endl;
    std::cout << "2 - push front" << std::endl;
    std::cout << "3 - push back" << std::endl;
    std::cout << "4 - pop front" << std::endl;
    std::cout << "5 - pop back" << std::endl;
    std::cout << "6 - get subsequence" << std::endl;
    std::cout << "7 - concat" << std::endl;

    int user_input;
    std::cout << ">>> ";
    std::cin >> user_input;
    panic_if_invalid_input("action");

    switch (user_input) {
        case 1:
            return EXIT;
        case 2:
            return PUSH_FRONT;
        case 3:
            return PUSH_BACK;
        case 4:
            return POP_FRONT;
        case 5:
            return POP_BACK;
        case 6:
            return GET_SUBSEQUENCE;
        case 7:
            return CONCAT;
        default:
            throw kogan::InvalidArgumentException("action");
    }
}


void print_containers(struct QueueStackDeque& containers) {
    std::cout << "Queue: " << *containers.queue << std::endl;
    std::cout << "Stack: " << *containers.stack << std::endl;
    std::cout << "Deque: " << *containers.deque << std::endl;
}


void push_queue_menu(kogan::Queue<int>* queue) {
    log_blue("Push value"); std::cout << std::endl;

    std::cout << "value: ";
    int value; std::cin >> value;
    panic_if_invalid_input("value");

    queue->push(value);
}


void push_stack_menu(kogan::Stack<int>* stack) {
    log_blue("Push value"); std::cout << std::endl;

    std::cout << "value: ";
    int value; std::cin >> value;
    panic_if_invalid_input("value");

    stack->push(value);
}


void pop_queue_menu(kogan::Queue<int>* queue) {
    log_blue("Pop value"); std::cout << std::endl;

    std::cout << "value: " << queue->pop() << std::endl;
}


void pop_stack_menu(kogan::Stack<int>* stack) {
    log_blue("Pop value"); std::cout << std::endl;

    std::cout << "value: " << stack->pop() << std::endl;
}


void push_front_deque_menu(kogan::Deque<int>* deque) {
    log_blue("Push front value"); std::cout << std::endl;

    std::cout << "value: ";
    int value; std::cin >> value;
    panic_if_invalid_input("value");

    deque->push_front(value);
}


void pop_front_deque_menu(kogan::Deque<int>* deque) {
    log_blue("Pop front value"); std::cout << std::endl;

    std::cout << "value: " << deque->pop_front() << std::endl;
}


void push_back_deque_menu(kogan::Deque<int>* deque) {
    log_blue("Push back value"); std::cout << std::endl;

    std::cout << "value: ";
    int value; std::cin >> value;
    panic_if_invalid_input("value");

    deque->push_back(value);
}


void pop_back_deque_menu(kogan::Deque<int>* deque) {
    log_blue("Pop back value"); std::cout << std::endl;

    std::cout << "value: " << deque->pop_back() << std::endl;
}


void get_subsequence_menu(kogan::BaseContainer<int>* container) {
    log_blue("Get subsequence"); std::cout << std::endl;

    std::cout << "start index: ";
    int start_index; std::cin >> start_index;
    panic_if_invalid_input("start index");

    std::cout << "end index: ";
    int end_index; std::cin >> end_index;
    panic_if_invalid_input("end index");

    kogan::Sequence<int>* sub_seq = container->get_subsequence(start_index, end_index);
    std::cout << "Subsequence: " << std::endl << *sub_seq << std::endl << std::endl;
    delete sub_seq;
}


void concat_queue_menu(kogan::Queue<int>* queue) {
    log_blue("Concatenate"); std::cout << std::endl;

    std::cout << "Other queue's length: ";
    int other_length; std::cin >> other_length;
    panic_if_invalid_input("other_length");
    if (other_length < 0)
        throw kogan::InvalidArgumentException("other_length");

    kogan::Queue<int> other_queue;
    if (other_length > 0) {
        std::cout << "Input other queue's values: " << std::endl;
        for (int i = 0; i < other_length; ++i) {
            int val; std::cin >> val;
            panic_if_invalid_input("queue value");
            other_queue.push(val);
        }
    }

    kogan::Queue<int>* concatenation = queue->concat(other_queue);
    std::cout << "First queue: " << *queue << std::endl;
    std::cout << "Second queue: " << other_queue << std::endl;
    std::cout << "Concatenation: " << *concatenation << std::endl;
    delete concatenation;
}


void concat_stack_menu(kogan::Stack<int>* stack) {
    log_blue("Concatenate"); std::cout << std::endl;

    std::cout << "Other stack's length: ";
    int other_length; std::cin >> other_length;
    panic_if_invalid_input("other_length");
    if (other_length < 0)
        throw kogan::InvalidArgumentException("other_length");

    kogan::Stack<int> other_stack;
    if (other_length > 0) {
        std::cout << "Input other stack's values: " << std::endl;
        for (int i = 0; i < other_length; ++i) {
            int val; std::cin >> val;
            panic_if_invalid_input("queue value");
            other_stack.push(val);
        }
    }

    kogan::Stack<int>* concatenation = stack->concat(other_stack);
    std::cout << "First queue: " << *stack << std::endl;
    std::cout << "Second queue: " << other_stack << std::endl;
    std::cout << "Concatenation: " << *concatenation << std::endl;
    delete concatenation;
}


void concat_deque_menu(kogan::Deque<int>* deque) {
    log_blue("Concatenate"); std::cout << std::endl;

    std::cout << "Other stack's length: ";
    int other_length; std::cin >> other_length;
    panic_if_invalid_input("other_length");
    if (other_length < 0)
        throw kogan::InvalidArgumentException("other_length");

    kogan::Deque<int> other_deque;
    if (other_length > 0) {
        std::cout << "Input other stack's values: " << std::endl;
        for (int i = 0; i < other_length; ++i) {
            int val; std::cin >> val;
            panic_if_invalid_input("queue value");
            other_deque.push_back(val);
        }
    }

    kogan::Deque<int>* concatenation = deque->concat(other_deque);
    std::cout << "First queue: " << *deque << std::endl;
    std::cout << "Second queue: " << other_deque << std::endl;
    std::cout << "Concatenation: " << *concatenation << std::endl;
    delete concatenation;
}


void panic_if_invalid_input(std::string argument_name) {
    if (!std::cin.good()) {
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        throw kogan::InvalidArgumentException(std::move(argument_name));
    }
}
