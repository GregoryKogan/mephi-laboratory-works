#include "libs/matrix.h"
#include "libs/types/int_type.h"
#include "libs/IO/logger.h"
//#include "libs/types/float_type.h"

int main() {
    error* err = error_ctor();

    type_t* int_type = int_type_ctor(err);
    if (err->raised) log_fatal_error(err);

    matrix_t* matrix_a = matrix_ctor(err, int_type, 3, 4);
    if (err->raised) log_fatal_error(err);

    if (matrix_a) matrix_print(err, matrix_a);
    if (err->raised) log_error(err);

    matrix_dtor(matrix_a);

    error_dtor(err);
    return 0;
}
