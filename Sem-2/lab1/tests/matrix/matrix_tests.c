//
// Created by Gregory Kogan on 07.03.2023.
//

#include "matrix_tests.h"


bool constructor_dimensions_test() {
    bool result = true;
    matrix_t* m = matrix_ctor(int_type_ctor(), 3, 4);

    if (matrix_get_width(m) != 4 || matrix_get_height(m) != 3)
        result = false;

    if (*(int *)matrix_get_value(m, 0, 0) != *(int *)(m->type->zero))
        result = false;

    matrix_dtor(m);
    return result;
}

bool constructor_initial_values_test() {
    bool result = true;
    matrix_t* m = matrix_ctor(int_type_ctor(), 2, 2);

    if (*(int *)matrix_get_value(m, 0, 0) != *(int *)(m->type->zero))
        result = false;

    matrix_dtor(m);
    return result;
}

bool constructor_edge_cases_test() {
    bool result = true;

    matrix_t* m = matrix_ctor(int_type_ctor(), 0, 0);
    if (m != NULL) result = false;
    matrix_dtor(m);

    m = matrix_ctor(int_type_ctor(), 3, 0);
    if (m != NULL) result = false;
    matrix_dtor(m);

    m = matrix_ctor(int_type_ctor(), 0, 7);
    if (m != NULL) result = false;
    matrix_dtor(m);

    return result;
}

bool multiplication_test() {
    matrix_t* matrix_a = matrix_ctor(int_type_ctor(), 3, 4);
    matrix_t* matrix_b = matrix_ctor(int_type_ctor(), 4, 3);
    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 4; ++j) {
            int x = i + j;
            matrix_set_value(matrix_a, i, j, &x);
            matrix_set_value(matrix_b, j, i, &x);
        }
    }

    bool result = true;
    matrix_t* mul = matrix_mul(matrix_a, matrix_b);
    if (matrix_get_width(mul) != 3 || matrix_get_height(mul) != 3)
        result = false;

    int target[9] = {
        14, 20, 26,
        20, 30, 40,
        26, 40, 54
    };
    if (result) {
        for (size_t i = 0; i < 9; ++i) {
            if (*((int *) matrix_get_value(mul, i / 3, i % 3)) != target[i])
                result = false;
        }
    }

    matrix_dtor(mul);
    matrix_dtor(matrix_a);
    matrix_dtor(matrix_b);

    return result;
}

bool multiplication_size_conflict_test() {
    matrix_t* matrix_a = matrix_ctor(float_type_ctor(), 3, 6);
    matrix_t* matrix_b = matrix_ctor(int_type_ctor(), 4, 3);
    bool result = true;
    matrix_t* mul = matrix_mul(matrix_a, matrix_b);

    if (mul != NULL) result = false;

    matrix_dtor(mul);
    matrix_dtor(matrix_a);
    matrix_dtor(matrix_b);
    return result;
}

bool multiplication_type_conflict_test() {
    matrix_t* matrix_a = matrix_ctor(float_type_ctor(), 3, 4);
    matrix_t* matrix_b = matrix_ctor(int_type_ctor(), 4, 3);
    bool result = true;
    matrix_t* mul = matrix_mul(matrix_a, matrix_b);

    if (mul != NULL) result = false;

    matrix_dtor(mul);
    matrix_dtor(matrix_a);
    matrix_dtor(matrix_b);
    return result;
}

test_t** get_matrix_tests(size_t* tests_num) {
    *tests_num = 6;
    test_t** tests = malloc(sizeof(test_t) * (*tests_num));
    if (tests == NULL)
        log_error_and_exit("can't allocate memory", 3);

    tests[0] = test_ctor("matrix constructor dimensions", constructor_dimensions_test);
    tests[1] = test_ctor("matrix constructor initial values", constructor_initial_values_test);
    tests[2] = test_ctor("matrix constructor edge cases", constructor_edge_cases_test);
    tests[3] = test_ctor("matrix multiplication", multiplication_test);
    tests[4] = test_ctor("matrix multiplication size conflict", multiplication_size_conflict_test);
    tests[5] = test_ctor("matrix multiplication type conflict", multiplication_type_conflict_test);

    return tests;
}
