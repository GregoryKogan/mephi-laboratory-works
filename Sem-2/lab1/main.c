#include "libs/matrix.h"
#include "libs/types/int_type.h"

int main() {
    matrix_t* my_matrix = matrix_ctor(int_type_ctor(), 5, 7);

    for (int i = 0; i < 7; ++i) {
        int x = i + 1;
        matrix_set_value(my_matrix, i % 5, i, &x);
    }
    matrix_print(my_matrix);
    matrix_dtor(my_matrix);
    return 0;
}
