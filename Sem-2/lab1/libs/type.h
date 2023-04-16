//
// Created by Gregory Kogan on 26.02.2023.
//

#ifndef LAB1_TYPE_H
#define LAB1_TYPE_H

#include <stdlib.h>
#include "Errors/error.h"

typedef struct Type_t{
    const char* name;
    void* zero;
    void* one;
    void* (*from_instance)(error*, const void*);
    void (*free_memory)(void*);
    void (*add)(void*, void*, void*);
    void (*sub)(void*, void*, void*);
    void (*mul)(void*, void*, void*);
    char* (*to_string)(error*, void*);
} type_t;

type_t* type_ctor(
    error *,
    const char* name,
    void* zero,
    void* one,
    void* (*from_instance)(error*, const void*),
    void (*free_memory)(void*),
    void (*add)(void*, void*, void*),
    void (*sub)(void*, void*, void*),
    void (*mul)(void*, void*, void*),
    char* (*to_string)(error*, void*)
);
void type_dtor(type_t* self);
type_t* type_copy(error*, type_t*);

#endif //LAB1_TYPE_H
