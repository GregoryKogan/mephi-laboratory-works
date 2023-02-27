//
// Created by Gregory Kogan on 26.02.2023.
//

#include "type.h"


type_t* type_ctor(
        size_t size,
        void* zero,
        void* one,
        void* (*add)(void*, void*),
        void* (*sub)(void*, void*),
        void* (*mul)(void*, void*),
        char* (*to_string)(void*)
) {
    type_t* type = (type_t*)malloc(sizeof(size_t));
    type->size = size;
    type->zero = zero;
    type->one = one;
    type->add = add;
    type->sub = sub;
    type->mul = mul;
    type->to_string = to_string;
    return type;
}

void type_dtor(type_t* self) {
//    free(self->zero);
//    free(self->one);
    free(self);
}
