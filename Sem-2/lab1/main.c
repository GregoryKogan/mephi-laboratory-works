#include "libs/matrix.h"
#include "libs/types/int_type.h"
//#include "libs/types/float_type.h"

int main() {
    matrix_t* matrix_a = matrix_ctor(int_type_ctor(), 0, 4);
    if (matrix_a)
        matrix_print(matrix_a);
    matrix_dtor(matrix_a);
    return 0;
}
