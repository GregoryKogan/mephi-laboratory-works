//
// Created by Gregory Kogan on 07.03.2023.
//

#include "matrix_tests.h"


bool constructor_dimensions_test(error* err) {
    bool result = true;
    matrix_t* m = matrix_ctor(err, int_type_ctor(err), 3, 4);

    if (matrix_get_width(m) != 4 || matrix_get_height(m) != 3)
        result = false;

    if (*(int *)matrix_get_value(err, m, 0, 0) != *(int *)(m->type->zero))
        result = false;

    matrix_dtor(m);
    return result;
}

bool constructor_initial_values_test(error* err) {
    bool result = true;
    matrix_t* m = matrix_ctor(err, int_type_ctor(err), 2, 2);

    if (*(int *)matrix_get_value(err, m, 0, 0) != *(int *)(m->type->zero))
        result = false;

    matrix_dtor(m);
    return result;
}

bool constructor_edge_cases_test(error* err) {
    bool result = true;

    type_t* int_type;
    matrix_t* m;

    int_type = int_type_ctor(err);
    m = matrix_ctor(err, int_type, 0, 0);
    if (m != NULL) {
        result = false;
        matrix_dtor(m);
    } else type_dtor(int_type);

    int_type = int_type_ctor(err);
    m = matrix_ctor(err, int_type, 3, 0);
    if (m != NULL) {
        result = false;
        matrix_dtor(m);
    } else type_dtor(int_type);

    int_type = int_type_ctor(err);
    m = matrix_ctor(err, int_type, 0, 7);
    if (m != NULL) {
        result = false;
        matrix_dtor(m);
    } else type_dtor(int_type);
    
    return result;
}

bool addition_of_scalar_test(error* err) {
    matrix_t* m = matrix_ctor(err, float_type_ctor(err), 3, 4);
    for (size_t i = 0; i < matrix_get_height(m); ++i) {
        for (size_t j = 0; j < matrix_get_width(m); ++j) {
            float x = (float)(i + 1) * (float)(j + 1);
            matrix_set_value(err, m, i, j, &x);
        }
    }

    float alpha = -3;
    matrix_t* res_m = matrix_add_scalar(err, m, &alpha);

    bool result = true;
    if (m == NULL || res_m == NULL)
        result = false;

    float target[12] = {
            -2, -1, 0, 1,
            -1, 1, 3, 5,
            0, 3, 6, 9
    };
    if (result) {
        for (size_t i = 0; i < 12; ++i) {
            if (fabsf(*((float *)matrix_get_value(err, res_m, i / 4, i % 4)) - target[i]) > 0.001)
                result = false;
        }
    }

    matrix_dtor(res_m);
    matrix_dtor(m);
    return result;
}

bool multiplication_test(error* err) {
    matrix_t* matrix_a = matrix_ctor(err, int_type_ctor(err), 3, 4);
    matrix_t* matrix_b = matrix_ctor(err, int_type_ctor(err), 4, 3);
    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 4; ++j) {
            int x = i + j;
            matrix_set_value(err, matrix_a, i, j, &x);
            matrix_set_value(err, matrix_b, j, i, &x);
        }
    }

    bool result = true;
    matrix_t* mul = matrix_mul(err, matrix_a, matrix_b);
    if (matrix_get_width(mul) != 3 || matrix_get_height(mul) != 3)
        result = false;

    int target[9] = {
        14, 20, 26,
        20, 30, 40,
        26, 40, 54
    };
    if (result) {
        for (size_t i = 0; i < 9; ++i) {
            if (*((int *) matrix_get_value(err, mul, i / 3, i % 3)) != target[i])
                result = false;
        }
    }

    matrix_dtor(mul);
    matrix_dtor(matrix_a);
    matrix_dtor(matrix_b);

    return result;
}

bool multiplication_size_conflict_test(error* err) {
    matrix_t* matrix_a = matrix_ctor(err, float_type_ctor(err), 3, 6);
    matrix_t* matrix_b = matrix_ctor(err, int_type_ctor(err), 4, 3);
    bool result = true;
    matrix_t* mul = matrix_mul(err, matrix_a, matrix_b);

    if (mul != NULL) result = false;

    matrix_dtor(mul);
    matrix_dtor(matrix_a);
    matrix_dtor(matrix_b);
    return result;
}

bool multiplication_type_conflict_test(error* err) {
    matrix_t* matrix_a = matrix_ctor(err, float_type_ctor(err), 3, 4);
    matrix_t* matrix_b = matrix_ctor(err, int_type_ctor(err), 4, 3);
    bool result = true;
    matrix_t* mul = matrix_mul(err, matrix_a, matrix_b);

    if (mul != NULL) result = false;

    matrix_dtor(mul);
    matrix_dtor(matrix_a);
    matrix_dtor(matrix_b);
    return result;
}

bool multiplication_by_scalar_test(error* err) {
    matrix_t* m = matrix_ctor(err, float_type_ctor(err), 3, 4);
    for (size_t i = 0; i < matrix_get_height(m); ++i) {
        for (size_t j = 0; j < matrix_get_width(m); ++j) {
            float x = (float)(i + 1) * (float)(j + 1);
            matrix_set_value(err, m, i, j, &x);
        }
    }

    float alpha = 3;
    matrix_t* res_m = matrix_mul_scalar(err, m, &alpha);

    bool result = true;
    if (m == NULL || res_m == NULL)
        result = false;

    float target[12] = {
            3, 6, 9, 12,
            6, 12, 18, 24,
            9, 18, 27, 36
    };
    if (result) {
        for (size_t i = 0; i < 12; ++i) {
            if (fabsf(*((float *)matrix_get_value(err, res_m, i / 4, i % 4)) - target[i]) > 0.001)
                result = false;
        }
    }

    matrix_dtor(res_m);
    matrix_dtor(m);
    return result;
}

bool linear_combination_test(error* err) {
    type_t* m_type = float_type_ctor(err);
    matrix_t* m = matrix_ctor(err, m_type, 3, 4);

    for (size_t i = 0; i < matrix_get_height(m); ++i) {
        for (size_t j = 0; j < matrix_get_width(m); ++j) {
            float x = (float)(i + 1) * (float)(j + 1);
            matrix_set_value(err, m, i, j, &x);
        }
    }

    float** alphas = malloc(sizeof(float*) * 2);
    float a1 = 2, a2 = 7;
    alphas[0] = &a1;
    alphas[1] = &a2;
    matrix_t* result_m = matrix_add_linear_combination(err, m, 1, (const void **) alphas);
    free(alphas);

    bool result = true;
    if (result_m == NULL)
            result = false;

    float target[12] = {
            1, 2, 3, 4,
            25, 50, 75, 100,
            3, 6, 9, 12
    };
    if (result) {
        for (size_t i = 0; i < 12; ++i) {
            if (fabsf(*((float *)matrix_get_value(err, result_m, i / 4, i % 4)) - target[i]) > 0.001)
                result = false;
        }
    }

    matrix_dtor(m);
    matrix_dtor(result_m);
    return result;
}

test_t** get_matrix_tests(error* err, size_t* tests_num) {
    *tests_num = 8;
    test_t** tests = malloc(sizeof(test_t) * (*tests_num));
    if (tests == NULL) {
        error_raise(err, "can't allocate memory");
        return NULL;
    }

    tests[0] = test_ctor(err, "matrix constructor dimensions", constructor_dimensions_test);
    tests[1] = test_ctor(err, "matrix constructor initial values", constructor_initial_values_test);
    tests[2] = test_ctor(err, "matrix constructor edge cases", constructor_edge_cases_test);
    tests[3] = test_ctor(err, "matrix addition of scalar", addition_of_scalar_test);
    tests[4] = test_ctor(err, "matrix multiplication", multiplication_test);
    tests[5] = test_ctor(err, "matrix multiplication size conflict", multiplication_size_conflict_test);
    tests[6] = test_ctor(err, "matrix multiplication type conflict", multiplication_type_conflict_test);
    tests[7] = test_ctor(err, "matrix multiplication by scalar", multiplication_by_scalar_test);
    tests[8] = test_ctor(err, "matrix linear combination", linear_combination_test);

    return tests;
}
