//
// Created by Gregory Kogan on 21.05.2023.
//

#include "trees/nary_tree.hpp"


int main() {
    kogan::NaryTree<int> tree(2);
    tree.get_root()->set_value(1);
    tree.get_root()->add_child(2);
    tree.get_root()->add_child(3);
    tree.get_root()->get_child(0)->add_child(4);
    tree.get_root()->get_child(0)->add_child(4);
    tree.get_root()->get_child(1)->add_child(5);
    std::cout << tree << std::endl;
    return 0;
}
