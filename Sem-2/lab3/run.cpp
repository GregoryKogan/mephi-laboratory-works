#include "sequence_lib.hpp"


int main() {
    kogan::LinkedListSequence<int> list;
    list.append(1);
    list.append(2);
    list.append(3);
    list.append(4);
    list.append(5);

    std::cout << list << std::endl;

    return 0;
}
