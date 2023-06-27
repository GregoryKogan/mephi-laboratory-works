//
// Created by Gregory Kogan on 21.05.2023.
//

#include "UI/menus.hpp"
#include "trees/nary_tree.hpp"
#include "trees/serializers/nary_tree_serializer.hpp"
#include <IO/colored_logs.hpp>

void interaction_loop(kogan::NaryTree<char> *tree) {
  action selected_action;
  do {
    try {
      for (int i = 0; i < 3; ++i)
        std::cout << std::endl;

      kogan::NaryTreeSerializer<char> serializer(*tree);
      std::cout << "N-ary tree: " << serializer.get_serialized_tree()
                << std::endl
                << std::endl;

      selected_action = select_action_menu();

      switch (selected_action) {
      case EXIT:
        break;
      case SIZE:
        size_menu(tree);
        break;
      case CHILDREN_COUNT:
        children_count_menu(tree);
        break;
      case HEIGHT:
        height_menu(tree);
        break;
      case SET:
        set_menu(tree);
        break;
      case ADD_CHILD:
        add_child_menu(tree);
        break;
      case REMOVE_CHILD:
        remove_child_menu(tree);
        break;
      case GET_CHILD:
        get_child_menu(tree);
        break;
      case TRAVERSE:
        traverse_menu(tree);
        break;
      case COUNT:
        count_menu(tree);
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
  kogan::NaryTree<char> tree('A', 5);

  interaction_loop(&tree);

  return 0;
}
