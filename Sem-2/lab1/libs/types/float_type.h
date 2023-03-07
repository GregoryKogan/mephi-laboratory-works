//
// Created by Gregory Kogan on 07.03.2023.
//

#ifndef LAB1_FLOAT_TYPE_H
#define LAB1_FLOAT_TYPE_H

#include <stdio.h>
#include "../type.h"

void* float_get_zero();
void* float_get_one();
void* float_from_instance(const void*);
void float_free_memory(void*);
void* float_add(void*, void*);
void* float_sub(void*, void*);
void* float_mul(void*, void*);
char* float_to_string(void*);

type_t* float_type_ctor();

#endif //LAB1_FLOAT_TYPE_H
