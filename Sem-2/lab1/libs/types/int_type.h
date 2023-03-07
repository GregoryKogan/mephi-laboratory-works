//
// Created by Gregory Kogan on 26.02.2023.
//

#ifndef LAB1_INT_TYPE_H
#define LAB1_INT_TYPE_H

#include <stdio.h>
#include "../type.h"

void* int_get_zero();
void* int_get_one();
void* int_from_instance(const void*);
void int_free_memory(void*);
void int_add(void*, void*, void*);
void int_sub(void*, void*, void*);
void int_mul(void*, void*, void*);
char* int_to_string(void*);

type_t* int_type_ctor();

#endif //LAB1_INT_TYPE_H
