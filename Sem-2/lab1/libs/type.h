//
// Created by Gregory Kogan on 26.02.2023.
//

#ifndef LAB1_TYPE_H
#define LAB1_TYPE_H

#include <stdlib.h>
#include "IO/logger.h"

typedef struct {
    size_t size;
    void* zero;
    void* one;
    void* (*add)(void*, void*);
    void* (*sub)(void*, void*);
    void* (*mul)(void*, void*);
    char* (*to_string)(void*);
} type_t;

type_t* type_ctor(
    size_t,
    void* zero,
    void* one,
    void* (*add)(void*, void*),
    void* (*sub)(void*, void*),
    void* (*mul)(void*, void*),
    char* (*to_string)(void*)
);
void type_dtor(type_t* self);

#endif //LAB1_TYPE_H
