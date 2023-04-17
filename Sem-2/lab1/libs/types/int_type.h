//
// Created by Gregory Kogan on 26.02.2023.
//

#ifndef LAB1_INT_TYPE_H
#define LAB1_INT_TYPE_H

#include <stdio.h>
#include "../type.h"

void* int_get_zero(error*);
void* int_get_one(error*);
void* int_from_instance(error*, const void*);
void int_free_memory(void*);
void int_add(void*, const void*, const void*);
void int_sub(void*, const void*, const void*);
void int_mul(void*, const void*, const void*);
void int_random(void*);
char* int_to_string(error*, void*);

type_t* int_type_ctor(error*);

#endif //LAB1_INT_TYPE_H
