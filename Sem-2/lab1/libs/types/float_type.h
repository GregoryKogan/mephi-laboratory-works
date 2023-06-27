//
// Created by Gregory Kogan on 07.03.2023.
//

#ifndef LAB1_FLOAT_TYPE_H
#define LAB1_FLOAT_TYPE_H

#include "../type.h"
#include <stdio.h>

void *float_get_zero(error *);
void *float_get_one(error *);
void *float_from_instance(error *, const void *);
void float_free_memory(void *);
void float_add(void *, const void *, const void *);
void float_sub(void *, const void *, const void *);
void float_mul(void *, const void *, const void *);
void float_random(void *);
char *float_to_string(error *, void *);

type_t *float_type_ctor(error *);

#endif // LAB1_FLOAT_TYPE_H
