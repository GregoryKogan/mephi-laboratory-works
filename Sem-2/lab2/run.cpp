#include <iostream>
#include "sequences/ArraySequence.h"
#include "sequences/LinkedListSequence.h"
#include "UI/menus.h"
#include "IO/colored_logs.h"


void interaction_loop(kogan::ArraySequence<int>* array_seq, kogan::LinkedListSequence<int>* linked_list_seq) {
    action selected_action = SELECT_ACTION;

    while (selected_action != EXIT) {
        try {
            switch (selected_action) {
                case SELECT_ACTION:
                    selected_action = select_action_menu(array_seq, linked_list_seq);
                    break;
                case INPUT:
                    input_menu(array_seq, linked_list_seq);
                    selected_action = SELECT_ACTION;
                    break;
                case SET:
                    set_menu(array_seq, linked_list_seq);
                    selected_action = SELECT_ACTION;
                    break;
                case APPEND:
                    std::cout << "APPEND" << std::endl;
                    selected_action = SELECT_ACTION;
                    break;
                case PREPEND:
                    std::cout << "PREPEND" << std::endl;
                    selected_action = SELECT_ACTION;
                    break;
                case INSERT:
                    std::cout << "INSERT" << std::endl;
                    selected_action = SELECT_ACTION;
                    break;
                case CONCATENATE:
                    std::cout << "CONCATENATE" << std::endl;
                    selected_action = SELECT_ACTION;
                    break;
                case SUBSEQUENCE:
                    std::cout << "SUBSEQUENCE" << std::endl;
                    selected_action = SELECT_ACTION;
                    break;
                case LENGTH:
                    std::cout << "LENGTH" << std::endl;
                    selected_action = SELECT_ACTION;
                    break;
                default:
                    selected_action = SELECT_ACTION;
                    break;
            }
        } catch (std::exception& e) {
            log_red(e.what());
            std::cout << std::endl;
            selected_action = SELECT_ACTION;
        }
    }
}


int main() {
    kogan::ArraySequence<int> array_seq;
    kogan::LinkedListSequence<int> linked_list_seq;

    interaction_loop(&array_seq, &linked_list_seq);

    return 0;
}
