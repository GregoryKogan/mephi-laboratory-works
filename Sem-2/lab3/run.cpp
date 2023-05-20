#include "containers/deque/deque.hpp"


int main() {
    int values[10] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    kogan::Deque<int> d(values, 10);

    for (auto x: d) {
        std::cout << x << std::endl;
        x = 33;
    }

    for (auto x: d) {
        std::cout << x << std::endl;
    }

    return 0;
}
