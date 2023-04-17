//
// Created by Gregory Kogan on 26.02.2023.
//

#ifndef LAB1_MATRIX_H
#define LAB1_MATRIX_H

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "type.h"
#include "Errors/error.h"

typedef struct {
    size_t width;
    size_t height;
    type_t* type;
    void** data;
} matrix_t;

matrix_t* matrix_ctor(error*, type_t*, size_t, size_t);
void matrix_dtor(matrix_t* self);

size_t matrix_get_width(matrix_t* self);
size_t matrix_get_height(matrix_t* self);

void* matrix_get_value(error*, matrix_t* self, size_t, size_t);
void matrix_set_value(error*, matrix_t* self, size_t i, size_t j, const void* value);

void matrix_fill(error*, matrix_t* self, const void* value);
void matrix_random_fill(error*, matrix_t* self);

matrix_t* matrix_copy(error*, matrix_t* m);

matrix_t* matrix_transpose(error*, matrix_t* self);
matrix_t* matrix_add(error*, matrix_t* a, matrix_t* b);
matrix_t* matrix_add_scalar(error*, matrix_t* m, void* alpha);
matrix_t* matrix_mul(error*, matrix_t* a, matrix_t* b);
matrix_t* matrix_mul_scalar(error*, matrix_t* m, void* alpha);
matrix_t* matrix_add_linear_combination(error*, matrix_t* m, size_t row_index, const void** alphas);

char* matrix_to_string(error*, matrix_t* self);
void matrix_print(error*, matrix_t* self);

#endif //LAB1_MATRIX_H
