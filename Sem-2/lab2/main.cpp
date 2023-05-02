#include <iostream>
#include "data_structures/DynamicArray.h"


int main() {
    int* values = new int[10];
    for (int i = 0; i < 10; ++i)
        values[i] = i + 100;

    kogan::DynamicArray<int> d(values, 10);
    kogan::DynamicArray<int> c(d);
    c.resize(3);

    for (int i = 0; i < d.get_length(); ++i) {
        std::cout << d.get(i) << " ";
    }
    std::cout << std::endl;

    for (int i = 0; i < c.get_length(); ++i) {
        std::cout << c.get(i) << " ";
    }
    std::cout << std::endl;

    delete [] values;
    return 0;
}
