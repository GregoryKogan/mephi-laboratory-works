#include "libs/matrix.h"
#include "libs/types/int_type.h"
#include "libs/types/float_type.h"

int main() {
    matrix_t* matrix_a = matrix_ctor(int_type_ctor(), 3, 4);
    matrix_t* matrix_b = matrix_ctor(float_type_ctor(), 3, 4);
    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 4; ++j) {
//            float x = (float)i + (float)j;
            int x = i + j;
            matrix_set_value(matrix_a, i, j, &x);
            matrix_set_value(matrix_b, i, j, &x);
        }
    }
    matrix_print(matrix_a);

    matrix_t* matrix_sum = matrix_add(matrix_a, matrix_b);
    matrix_print(matrix_sum);

    matrix_dtor(matrix_sum);
    matrix_dtor(matrix_a);
    matrix_dtor(matrix_b);
    return 0;
}
