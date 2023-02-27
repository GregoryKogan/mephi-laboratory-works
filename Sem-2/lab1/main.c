#include "libs/matrix.h"
#include "libs/types/int_type.h"

int main() {
    matrix_t* my_matrix = matrix_ctor(int_type_ctor(), 3, 4);
    matrix_print(my_matrix);
    matrix_dtor(my_matrix);
    return 0;
}
