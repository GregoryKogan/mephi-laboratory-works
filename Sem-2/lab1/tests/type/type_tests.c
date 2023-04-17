//
// Created by Gregory Kogan on 17.04.2023.
//

#include "type_tests.h"


bool addition_int_test(error* err) {
    type_t* int_type = int_type_ctor(err);

    int a = 6, b = 12;
    int sum;
    int_type->add(&sum, &a, &b);

    return (sum == 18);
}

bool addition_float_test(error* err) {
    type_t* float_type = float_type_ctor(err);

    float a = 6, b = 12;
    float sum;
    float_type->add(&sum, &a, &b);

    return (fabsf(sum - 18) < 0.001);
}

bool subtraction_int_test(error* err) {
    type_t* int_type = int_type_ctor(err);

    int a = 6, b = 12;
    int sub;
    int_type->sub(&sub, &a, &b);

    return (sub == -6);
}

bool subtraction_float_test(error* err) {
    type_t* float_type = float_type_ctor(err);

    float a = 6, b = 12;
    float sub;
    float_type->sub(&sub, &a, &b);

    return (fabsf(sub - (-6)) < 0.001);
}

bool multiplication_int_test(error* err) {
    type_t* int_type = int_type_ctor(err);

    int a = 6, b = -3;
    int mul;
    int_type->mul(&mul, &a, &b);

    return (mul == -18);
}

bool multiplication_float_test(error* err) {
    type_t* float_type = float_type_ctor(err);

    float a = 6, b = -3;
    float mul;
    float_type->mul(&mul, &a, &b);

    return (fabsf(mul - (-18)) < 0.001);
}

test_t** get_type_tests(error* err, size_t* tests_num) {
    *tests_num = 6;
    test_t** tests = malloc(sizeof(test_t) * (*tests_num));
    if (tests == NULL) {
        error_raise(err, "can't allocate memory");
        return NULL;
    }

    tests[0] = test_ctor(err, "type addition int", addition_int_test);
    tests[1] = test_ctor(err, "type addition float", addition_float_test);
    tests[2] = test_ctor(err, "type subtraction int", subtraction_int_test);
    tests[3] = test_ctor(err, "type subtraction float", subtraction_float_test);
    tests[4] = test_ctor(err, "type multiplication int", multiplication_int_test);
    tests[5] = test_ctor(err, "type multiplication float", multiplication_float_test);


    return tests;
}
