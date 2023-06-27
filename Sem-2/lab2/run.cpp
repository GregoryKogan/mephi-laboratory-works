#include "IO/colored_logs.hpp"
#include "UI/menus.hpp"
#include "sequences/ArraySequence.hpp"
#include "sequences/LinkedListSequence.hpp"
#include <iostream>

void interaction_loop(kogan::ArraySequence<int> *array_seq,
                      kogan::LinkedListSequence<int> *linked_list_seq) {
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
        append_menu(array_seq, linked_list_seq);
        selected_action = SELECT_ACTION;
        break;
      case PREPEND:
        prepend_menu(array_seq, linked_list_seq);
        selected_action = SELECT_ACTION;
        break;
      case INSERT:
        insert_menu(array_seq, linked_list_seq);
        selected_action = SELECT_ACTION;
        break;
      case CONCATENATE:
        concatenate_menu(array_seq, linked_list_seq);
        selected_action = SELECT_ACTION;
        break;
      case SUBSEQUENCE:
        subsequence_menu(array_seq, linked_list_seq);
        selected_action = SELECT_ACTION;
        break;
      case REMOVE:
        remove_menu(array_seq, linked_list_seq);
        selected_action = SELECT_ACTION;
        break;
      case CLEAR:
        clear_menu(array_seq, linked_list_seq);
        selected_action = SELECT_ACTION;
        break;
      case LENGTH:
        length_menu(array_seq, linked_list_seq);
        selected_action = SELECT_ACTION;
        break;
      default:
        selected_action = SELECT_ACTION;
        break;
      }
    } catch (std::exception &e) {
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
