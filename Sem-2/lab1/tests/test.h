//
// Created by Gregory Kogan on 07.03.2023.
//

#ifndef LAB1_TEST_H
#define LAB1_TEST_H

#include <stdbool.h>
#include <stdlib.h>
#include "../libs/IO/logger.h"


typedef struct {
    const char* name;
    bool (*test_func) (void);
} test_t;
test_t* test_ctor(const char* name, bool (*test_func) (void));
void test_dtor(test_t* self);

#endif //LAB1_TEST_H
