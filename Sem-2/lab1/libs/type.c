//
// Created by Gregory Kogan on 26.02.2023.
//

#include "type.h"


type_t* type_ctor(
        const char* name,
        void* zero,
        void* one,
        void* (*from_instance)(const void*),
        void (*free_memory)(void*),
        void* (*add)(void*, void*),
        void* (*sub)(void*, void*),
        void* (*mul)(void*, void*),
        char* (*to_string)(void*)
) {
    type_t* type = (type_t*)malloc(sizeof(type_t));
    if (type == NULL)
        log_error_and_exit("can't allocate memory", 3);

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

type_t* type_copy(type_t* original) {
    return type_ctor(
            original->name,
            original->from_instance(original->zero),
            original->from_instance(original->one),
            original->from_instance,
            original->free_memory,
            original->add,
            original->sub,
            original->mul,
            original->to_string
    );
}
