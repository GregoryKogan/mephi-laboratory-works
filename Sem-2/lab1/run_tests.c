//
// Created by Gregory Kogan on 07.03.2023.
//

#include <stdio.h>
#include "tests/type/type_tests.h"
#include "tests/matrix/matrix_tests.h"
#include "libs/IO/logger.h"


int main(void){
    error* err = error_ctor();

    size_t type_tests_num, matrix_tests_num;
    test_t** type_tests = get_type_tests(err, &type_tests_num);
    test_t** matrix_tests = get_matrix_tests(err, &matrix_tests_num);
    for (size_t i = 0; i < type_tests_num + matrix_tests_num; ++i) {
        test_t* test;
        if (i < type_tests_num) test = type_tests[i];
        else test = matrix_tests[i - type_tests_num];

        bool result = test->test_func(err);
        if (result) log_green("Passed - ");
        else log_red("Failed - ");
        printf("%s\n", test->name);

        test_dtor(test);
    }

    free(type_tests);
    free(matrix_tests);
    error_dtor(err);
    return 0;
}
