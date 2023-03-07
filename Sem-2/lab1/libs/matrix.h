//
// Created by Gregory Kogan on 26.02.2023.
//

#ifndef LAB1_MATRIX_H
#define LAB1_MATRIX_H

#include <stdlib.h>
#include <string.h>
#include "type.h"
#include "IO/logger.h"

typedef struct {
    size_t width;
    size_t height;
    type_t* type;
    void** data;
} matrix_t;

matrix_t* matrix_ctor(type_t*, size_t, size_t);
void matrix_dtor(matrix_t* self);

size_t matrix_get_width(matrix_t* self);
size_t matrix_get_height(matrix_t* self);

void* matrix_get_value(matrix_t* self, size_t, size_t);
void matrix_set_value(matrix_t* self, size_t i, size_t j, const void* value);

matrix_t* matrix_transpose(matrix_t* self);
matrix_t* matrix_add(matrix_t* a, matrix_t* b);
matrix_t* matrix_mul(matrix_t* a, matrix_t* b);

char* matrix_to_string(matrix_t* self);
void matrix_print(matrix_t* self);

#endif //LAB1_MATRIX_H
