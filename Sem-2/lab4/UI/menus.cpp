//
// Created by Gregory Kogan on 28.05.2023.
//

#include "menus.hpp"
#include "../trees/serializers/nary_tree_serializer.hpp"

action select_action_menu() {
  log_blue("Select action: ");
  std::cout << std::endl;
  std::cout << "0 - exit program" << std::endl;
  std::cout << "1 - size" << std::endl;
  std::cout << "2 - count children" << std::endl;
  std::cout << "3 - height" << std::endl;
  std::cout << "4 - set" << std::endl;
  std::cout << "5 - add child" << std::endl;
  std::cout << "6 - remove child" << std::endl;
  std::cout << "7 - get child" << std::endl;
  std::cout << "8 - traverse" << std::endl;
  std::cout << "9 - count" << std::endl;

  int user_input;
  std::cout << ">>> ";
  std::cin >> user_input;
  panic_if_invalid_input("action");

  switch (user_input) {
  case 0:
    return EXIT;
  case 1:
    return SIZE;
  case 2:
    return CHILDREN_COUNT;
  case 3:
    return HEIGHT;
  case 4:
    return SET;
  case 5:
    return ADD_CHILD;
  case 6:
    return REMOVE_CHILD;
  case 7:
    return GET_CHILD;
  case 8:
    return TRAVERSE;
  case 9:
    return COUNT;
  default:
    throw kogan::InvalidArgumentException("action");
  }
}

void size_menu(kogan::NaryTree<char> *tree) {
  log_blue("Get size");
  std::cout << std::endl;

  std::cout << "size: " << tree->size() << std::endl;
}

void children_count_menu(kogan::NaryTree<char> *tree) {
  log_blue("Count children");
  std::cout << std::endl;

  std::cout << "amount of children: " << tree->children_count() << std::endl;
}

void height_menu(kogan::NaryTree<char> *tree) {
  log_blue("Get height");
  std::cout << std::endl;

  std::cout << "height: " << tree->height() << std::endl;
}

void set_menu(kogan::NaryTree<char> *tree) {
  log_blue("Set value");
  std::cout << std::endl;

  std::cout << "value: ";
  char value;
  std::cin >> value;
  panic_if_invalid_input("value");

  tree->set_data(value);
}

void add_child_menu(kogan::NaryTree<char> *tree) {
  log_blue("Add child");
  std::cout << std::endl;

  std::cout << "value: ";
  char value;
  std::cin >> value;
  panic_if_invalid_input("value");

  tree->add_child(value);
}

void remove_child_menu(kogan::NaryTree<char> *tree) {
  log_blue("Remove child");
  std::cout << std::endl;

  std::cout << "index: ";
  int index;
  std::cin >> index;
  panic_if_invalid_input("index");

  tree->remove_child(index);
}

void get_child_menu(kogan::NaryTree<char> *tree) {
  log_blue("Get child");
  std::cout << std::endl;

  std::cout << "index: ";
  int index;
  std::cin >> index;
  panic_if_invalid_input("index");

  kogan::NaryTreeSerializer<char> serializer(*tree->get_child(index));
  std::cout << serializer.get_serialized_tree() << std::endl;
}

void traverse_menu(kogan::NaryTree<char> *tree) {
  log_blue("Traverse");
  std::cout << std::endl;

  kogan::Sequence<char> *NLR =
      tree->traverse(kogan::NaryTree<char>::TraverseType::ROOT_LEFT_RIGHT);
  kogan::Sequence<char> *NRL =
      tree->traverse(kogan::NaryTree<char>::TraverseType::ROOT_RIGHT_LEFT);
  kogan::Sequence<char> *LRN =
      tree->traverse(kogan::NaryTree<char>::TraverseType::LEFT_RIGHT_ROOT);
  kogan::Sequence<char> *RLN =
      tree->traverse(kogan::NaryTree<char>::TraverseType::RIGHT_LEFT_ROOT);

  std::cout << "Root-Left-Right: " << *NLR << std::endl;
  std::cout << "Root-Right-Left: " << *NRL << std::endl;
  std::cout << "Left-Right-Root: " << *LRN << std::endl;
  std::cout << "Right-Left-Root: " << *RLN << std::endl;

  delete NLR;
  delete NRL;
  delete LRN;
  delete RLN;
}

void count_menu(kogan::NaryTree<char> *tree) {
  log_blue("Count");
  std::cout << std::endl;

  std::cout << "value: ";
  char value;
  std::cin >> value;
  panic_if_invalid_input("value");

  std::cout << "amount of '" << value << "': " << tree->count(value)
            << std::endl;
}

void panic_if_invalid_input(const std::string &argument_name) {
  if (!std::cin.good()) {
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    throw kogan::InvalidArgumentException(argument_name);
  }
}
