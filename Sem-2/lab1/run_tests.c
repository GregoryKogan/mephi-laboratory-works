//
// Created by Gregory Kogan on 07.03.2023.
//

#include <stdio.h>
#include "tests/matrix/matrix_tests.h"
#include "libs/IO/logger.h"


int main(void){
    size_t tests_num;
    test_t** matrix_tests = get_matrix_tests(&tests_num);
    for (size_t i = 0; i < tests_num; ++i) {
        bool result = (matrix_tests[i])->test_func();
        if (result) green_print("Passed - ");
        else red_print("Error  - ");
        printf("%s\n", (matrix_tests[i])->name);

        test_dtor(matrix_tests[i]);
    }
    free(matrix_tests);
    return 0;
}
