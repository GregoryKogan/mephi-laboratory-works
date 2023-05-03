#include <iostream>
#include "data_structures/DynamicArray.h"
#include "data_structures/LinkedList.h"


void logic() {
    int* values = new int[10];
    for (int i = 0; i < 10; ++i)
        values[i] = i + 1;

    kogan::LinkedList<int> ll(values, 10);
    kogan::LinkedList<int> ll2 = ll.get_sublist(0, 9);

    ll2.insert(42, 5);

    for (int i = 0; i < ll.get_length(); ++i)
        std::cout << ll.get(i) << " ";
    std::cout << std::endl;

    for (int i = 0; i < ll2.get_length(); ++i)
        std::cout << ll2.get(i) << " ";
    std::cout << std::endl;

    kogan::LinkedList<int> ll3 = ll2.concat(ll);

    for (int i = 0; i < ll3.get_length(); ++i)
        std::cout << ll3.get(i) << " ";
    std::cout << std::endl;

    delete [] values;
}


int main() {
    try {
        logic();
    } catch (std::exception& e) {
        std::cerr << e.what() << std::endl;
    }
    return 0;
}
