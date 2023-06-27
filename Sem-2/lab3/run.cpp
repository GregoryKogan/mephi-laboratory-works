#include "UI/menus.hpp"
#include <IO/colored_logs.hpp>

void interaction_loop(struct QueueStackDeque &containers) {
  action selected_action;
  do {
    try {
      container_type selected_container = select_container_menu(containers);

      switch (selected_container) {
      case QUEUE:
        selected_action = select_queue_action_menu();
        break;
      case STACK:
        selected_action = select_stack_action_menu();
        break;
      case DEQUE:
        selected_action = select_deque_action_menu();
        break;
      default:
        throw kogan::InvalidArgumentException("action");
      }

      switch (selected_action) {
      case EXIT:
        break;
      case PUSH:
        switch (selected_container) {
        case QUEUE:
          push_queue_menu(containers.queue);
          break;
        case STACK:
          push_stack_menu(containers.stack);
          break;
        default:
          throw kogan::InvalidArgumentException("action");
        }
        break;
      case POP:
        switch (selected_container) {
        case QUEUE:
          pop_queue_menu(containers.queue);
          break;
        case STACK:
          pop_stack_menu(containers.stack);
          break;
        default:
          throw kogan::InvalidArgumentException("action");
        }
        break;
      case PUSH_FRONT:
        switch (selected_container) {
        case DEQUE:
          push_front_deque_menu(containers.deque);
          break;
        default:
          throw kogan::InvalidArgumentException("action");
        }
        break;
      case POP_FRONT:
        switch (selected_container) {
        case DEQUE:
          pop_front_deque_menu(containers.deque);
          break;
        default:
          throw kogan::InvalidArgumentException("action");
        }
        break;
      case PUSH_BACK:
        switch (selected_container) {
        case DEQUE:
          push_back_deque_menu(containers.deque);
          break;
        default:
          throw kogan::InvalidArgumentException("action");
        }
        break;
      case POP_BACK:
        switch (selected_container) {
        case DEQUE:
          pop_back_deque_menu(containers.deque);
          break;
        default:
          throw kogan::InvalidArgumentException("action");
        }
        break;
      case GET_SUBSEQUENCE:
        switch (selected_container) {
        case QUEUE:
          get_subsequence_menu(containers.queue);
          break;
        case STACK:
          get_subsequence_menu(containers.stack);
          break;
        case DEQUE:
          get_subsequence_menu(containers.deque);
          break;
        }
        break;
      case CONCAT:
        switch (selected_container) {
        case QUEUE:
          concat_queue_menu(containers.queue);
          break;
        case STACK:
          concat_stack_menu(containers.stack);
          break;
        case DEQUE:
          concat_deque_menu(containers.deque);
          break;
        }
        break;
      default:
        throw kogan::InvalidArgumentException("action");
      }
    } catch (std::exception &e) {
      log_red(e.what());
      std::cout << std::endl;
    }
  } while (selected_action != EXIT);
}

int main() {
  kogan::Queue<int> queue;
  kogan::Stack<int> stack;
  kogan::Deque<int> deque;

  struct QueueStackDeque containers = {&queue, &stack, &deque};

  interaction_loop(containers);

  return 0;
}
