//
// Created by Gregory Kogan on 07.03.2023.
//

#include "test.h"


test_t* test_ctor(error* err, const char* name, bool (*test_func) (error*)) {
    test_t* test = malloc(sizeof(test_t));
    if (test == NULL){
        error_raise(err, "can't allocate memory");
        return NULL;
    }
    test->name = name;
    test->test_func = test_func;
    return test;
}

void test_dtor(test_t* self) {
    free(self);
}
