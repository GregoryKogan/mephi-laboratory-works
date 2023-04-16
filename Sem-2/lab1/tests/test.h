//
// Created by Gregory Kogan on 07.03.2023.
//

#ifndef LAB1_TEST_H
#define LAB1_TEST_H

#include <stdbool.h>
#include <stdlib.h>
#include "../libs/Errors/error.h"


typedef struct {
    const char* name;
    bool (*test_func) (error*);
} test_t;
test_t* test_ctor(error*, const char* name, bool (*test_func) (error*));
void test_dtor(test_t* self);

#endif //LAB1_TEST_H
