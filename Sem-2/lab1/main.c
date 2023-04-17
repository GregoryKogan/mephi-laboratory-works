#include "libs/matrix.h"
//#include "libs/types/int_type.h"
#include "libs/IO/logger.h"
#include "libs/types/float_type.h"

int main() {
    error* err = error_ctor();

//    type_t* m_type = int_type_ctor(err);
    type_t* m_type = float_type_ctor(err);
    if (err->raised) log_fatal_error(err);

    matrix_t* m = matrix_ctor(err, m_type, 3, 4);
    if (err->raised) {
        type_dtor(m_type);
        log_fatal_error(err);
    }

    for (size_t i = 0; i < matrix_get_height(m); ++i) {
        for (size_t j = 0; j < matrix_get_width(m); ++j) {
//            int x = (int)(i + 1) * (int)(j + 1);
            float x = (float)(i + 1) * (float)(j + 1);
            matrix_set_value(err, m, i, j, &x);
        }
    }

    if (m) matrix_print(err, m);
    if (err->raised) log_error(err);

    float** alphas = malloc(sizeof(float*) * 2);
    float a1 = 2, a2 = 7;
    alphas[0] = &a1;
    alphas[1] = &a2;
    matrix_t* result = matrix_add_linear_combination(err, m, 1, (const void **) alphas);
    free(alphas);
    if (err->raised) log_error(err);
    if (result) matrix_print(err, result);

    matrix_dtor(m);
    matrix_dtor(result);
    error_dtor(err);
    return 0;
}
