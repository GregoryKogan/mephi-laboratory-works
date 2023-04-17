#include "libs/matrix.h"
#include "libs/types/int_type.h"
#include "libs/IO/logger.h"
#include "libs/types/float_type.h"

int main() {
    error* err = error_ctor();

    matrix_t* m = matrix_ctor(err, int_type_ctor(err), 3, 4);
    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 4; ++j) {
            int x = (i + 1) * (j + 1) + 3;
            matrix_set_value(err, m, i, j, &x);
        }
    }

    matrix_t* t = matrix_transpose(err, m);

    matrix_print(err, m);
    matrix_print(err, t);

    matrix_dtor(m);
    matrix_dtor(t);
    return 0;
}
