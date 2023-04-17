#include "libs/matrix.h"
#include "libs/types/int_type.h"
#include "libs/IO/logger.h"
#include "libs/types/float_type.h"

int main() {
    error* err = error_ctor();

    matrix_t* matrix_a = matrix_ctor(err, int_type_ctor(err), 3, 4);
    matrix_t* matrix_b = matrix_ctor(err, int_type_ctor(err), 3, 4);
    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 4; ++j) {
            int a_val = (i + 1) * (j + 1) + 3;
            int b_val = i + j - 2;
            matrix_set_value(err, matrix_a, i, j, &a_val);
            matrix_set_value(err, matrix_b, i, j, &b_val);
        }
    }

    matrix_t* sum = matrix_add(err, matrix_a, matrix_b);

    matrix_print(err, matrix_a);
    matrix_print(err, matrix_b);
    matrix_print(err, sum);

    matrix_dtor(matrix_a);
    matrix_dtor(matrix_b);
    matrix_dtor(sum);
    return 0;
}
