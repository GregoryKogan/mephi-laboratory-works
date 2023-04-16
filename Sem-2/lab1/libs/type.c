//
// Created by Gregory Kogan on 26.02.2023.
//

#include "type.h"


type_t* type_ctor(
        error* err,
        const char* name,
        void* zero,
        void* one,
        void* (*from_instance)(error*, const void*),
        void (*free_memory)(void*),
        void (*add)(void*, const void*, const void*),
        void (*sub)(void*, const void*, const void*),
        void (*mul)(void*, const void*, const void*),
        char* (*to_string)(error*, void*)
) {
    type_t* type = (type_t*)malloc(sizeof(type_t));
    if (type == NULL) {
        error_raise(err, "can't allocate memory");
        return NULL;
    }

    type->name = name;
    type->zero = zero;
    type->one = one;
    type->from_instance = from_instance;
    type->free_memory = free_memory;
    type->add = add;
    type->sub = sub;
    type->mul = mul;
    type->to_string = to_string;
    return type;
}

void type_dtor(type_t* self) {
    free(self->zero);
    free(self->one);
    free(self);
}

type_t* type_copy(error* err, type_t* original) {
    return type_ctor(
            err,
            original->name,
            original->from_instance(err, original->zero),
            original->from_instance(err, original->one),
            original->from_instance,
            original->free_memory,
            original->add,
            original->sub,
            original->mul,
            original->to_string
    );
}
