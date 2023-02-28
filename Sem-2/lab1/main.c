#include "libs/matrix.h"
#include "libs/types/int_type.h"

int main() {
    matrix_t* my_matrix = matrix_ctor(int_type_ctor(), 3, 4);
    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 4; ++j) {
            int x = i + j;
            matrix_set_value(my_matrix, i, j, &x);
        }
    }
    matrix_print(my_matrix);

    matrix_t* transposed = matrix_transpose(my_matrix);
    matrix_print(transposed);

    matrix_dtor(transposed);
    matrix_dtor(my_matrix);
    return 0;
}
