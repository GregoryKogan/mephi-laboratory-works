#include <iostream>
#include "sequences/ArraySequence.h"
#include "sequences/LinkedListSequence.h"


void logic() {
    kogan::LinkedListSequence<int> list;
    for (int i = 0; i < 10; ++i)
        list.append(i + 1);

    list[0] = 45;

    std::cout << list.to_string() << std::endl;
    std::cout << list[2] << std::endl;
}


int main() {
    try {
        logic();
    } catch (std::exception& e) {
        std::cerr << e.what() << std::endl;
    }

    return 0;
}
