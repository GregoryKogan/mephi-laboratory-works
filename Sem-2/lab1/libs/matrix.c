//
// Created by Gregory Kogan on 26.02.2023.
//

#include "matrix.h"

matrix_t* matrix_ctor(error* err, type_t* type, size_t height, size_t width) {
    if (height == 0 || width == 0) {
        error_raise(err, "matrix dimensions can't be 0");
        return NULL;
    }

    matrix_t* matrix = (matrix_t *)malloc(sizeof(matrix_t));
    if (matrix == NULL) {
        error_raise(err, "can't allocate memory");
        return NULL;
    }

    matrix->width = width;
    matrix->height = height;
    matrix->type = type;
    matrix->data = (void**)malloc(width * height * sizeof(void*));
    if (matrix->data == NULL) {
        error_raise(err, "can't allocate memory");
        return NULL;
    }

    for (size_t index = 0; index < height * width; ++index)
            matrix->data[index] = matrix->type->from_instance(err, matrix->type->zero);

    return matrix;
}

void matrix_dtor(matrix_t* self) {
    if (self == NULL) return;
    for (size_t i = 0; i < matrix_get_width(self) * matrix_get_height(self); ++i) {
        if (self->data[i] != NULL)
            self->type->free_memory(self->data[i]);
    }
    type_dtor(self->type);
    free(self->data);
    free(self);
}

size_t matrix_get_width(matrix_t* self) {
    return self->width;
}

size_t matrix_get_height(matrix_t* self) {
    return self->height;
}

void* matrix_get_value(error* err, matrix_t* self, size_t i, size_t j) {
    if (i >= matrix_get_height(self) || j >= matrix_get_width(self)) {
        error_raise(err, "matrix index out of range");
        return NULL;
    }
    size_t index = i * matrix_get_width(self) + j;
    return self->data[index];
}

void matrix_set_value(error* err, matrix_t* self, size_t i, size_t j, const void* value) {
    if (i >= matrix_get_height(self) || j >= matrix_get_width(self)) {
        error_raise(err, "matrix index out of range");
        return;
    }

    size_t index = i * matrix_get_width(self) + j;
    if (self->data[index] != NULL)
        self->type->free_memory(self->data[index]);
    self->data[index] = self->type->from_instance(err, value);
}

matrix_t* matrix_copy(error* err, matrix_t* m) {
    matrix_t* result = matrix_ctor(
            err,
            type_copy(err, m->type),
            matrix_get_height(m),
            matrix_get_width(m)
    );

    for (size_t i = 0; i < matrix_get_height(m); ++i) {
        for (size_t j = 0; j < matrix_get_width(m); ++j) {
            matrix_set_value(err, result, i, j, matrix_get_value(err, m, i, j));
        }
    }

    return result;
}

matrix_t* matrix_transpose(error* err, matrix_t* self) {
    matrix_t* result = matrix_ctor(err, type_copy(err, self->type), matrix_get_width(self), matrix_get_height(self));
    for (size_t j_ind = 0; j_ind < matrix_get_width(self); ++j_ind) {
        for (size_t i_ind = 0; i_ind < matrix_get_height(self); ++i_ind)
            matrix_set_value(err, result, j_ind, i_ind, matrix_get_value(err, self, i_ind, j_ind));
    }
    return result;
}

matrix_t* matrix_add(error* err, matrix_t* a, matrix_t* b) {
    if (strcmp(a->type->name, b->type->name) != 0) {
        error_raise(err, "matrix types do not match");
        return NULL;
    }
    if (matrix_get_height(a) != matrix_get_height(b) || matrix_get_width(a) != matrix_get_width(b)) {
        error_raise(err, "matrix sizes do not match");
        return NULL;
    }

    matrix_t* result = matrix_ctor(
        err,
        type_copy(err, a->type),
        matrix_get_height(a),
        matrix_get_width(a)
    );

    for (size_t i = 0; i < matrix_get_height(a); ++i) {
        for (size_t j = 0; j < matrix_get_width(a); ++j) {
            void* res_ptr = a->type->from_instance(err, a->type->zero);
            a->type->add(res_ptr, matrix_get_value(err, a, i, j), matrix_get_value(err, b, i, j));
            matrix_set_value(err, result, i, j, res_ptr);
            a->type->free_memory(res_ptr);
        }
    }

    return result;
}

matrix_t* matrix_mul(error* err, matrix_t* a, matrix_t* b) {
    if (strcmp(a->type->name, b->type->name) != 0) {
        error_raise(err, "matrix types do not match");
        return NULL;
    }
    if (matrix_get_width(a) != matrix_get_height(b)) {
        error_raise(err, "matrix sizes do not match");
        return NULL;
    }

    matrix_t* result = matrix_ctor(
            err,
            type_copy(err, a->type),
            matrix_get_height(a),
            matrix_get_width(b)
    );

    size_t iters = matrix_get_width(a);
    for (size_t a_row = 0; a_row < matrix_get_height(a); ++a_row) {
        for (size_t b_col = 0; b_col < matrix_get_width(b); ++b_col) {
            void* res_ptr = a->type->from_instance(err, a->type->zero);
            void* sum_buf = a->type->from_instance(err, a->type->zero);
            for (size_t iter = 0; iter < iters; ++iter) {
                a->type->mul(
                    sum_buf,
                    matrix_get_value(err, a, a_row, iter),
                    matrix_get_value(err, b, iter, b_col)
                );
                a->type->add(res_ptr, res_ptr, sum_buf);
            }
            matrix_set_value(err, result, a_row, b_col, res_ptr);
            a->type->free_memory(res_ptr);
            a->type->free_memory(sum_buf);
        }
    }

    return result;
}

matrix_t* matrix_mul_scalar(error* err, matrix_t* m, void* alpha) {
    matrix_t* result = matrix_copy(err, m);
    for (size_t i = 0; i < matrix_get_height(result); ++i) {
        for (size_t j = 0; j < matrix_get_width(result); ++j) {
            void* res_ptr = result->type->from_instance(err, result->type->zero);
            void* original_value = matrix_get_value(err, result, i, j);
            result->type->mul(res_ptr, alpha, original_value);
            matrix_set_value(err, result, i, j, res_ptr);
            result->type->free_memory(res_ptr);
        }
    }
    return result;
}

matrix_t* matrix_add_linear_combination(error* err, matrix_t* m, size_t row_index, const void** alphas) {
    matrix_t* result = matrix_copy(err, m);

    for (size_t i = 0; i < matrix_get_height(result); ++i) {
        if (i == row_index) continue;
        for (size_t j = 0; j < matrix_get_width(result); ++j) {
            size_t alpha_ind = i - (i > row_index);
            const void* alpha = alphas[alpha_ind];
            void* target_value = matrix_get_value(err, result, row_index, j);
            void* additive_value = matrix_get_value(err, result, i, j);
            void* res_ptr = result->type->from_instance(err, result->type->zero);
            result->type->mul(res_ptr, alpha, additive_value);
            result->type->add(res_ptr, target_value, res_ptr);
            matrix_set_value(err, result, row_index, j, res_ptr);
            result->type->free_memory(res_ptr);
        }
    }

    return result;
}

char* matrix_to_string(error* err, matrix_t* self) {
    char* str = (char*)malloc(sizeof(char) * matrix_get_width(self) * matrix_get_height(self) * 10 + 128);
    char* buff = (char*)malloc(sizeof(char) * 256);
    if (str == NULL || buff == NULL) {
        error_raise(err, "can't allocate memory");
        return NULL;
    }
	str[0] = '\0';
    size_t str_len = 0;

    snprintf(
        buff,
        256,
        "<Matrix [%lu x %lu]> (type: %s)\n",
        matrix_get_height(self),
        matrix_get_width(self),
        self->type->name
    );
    strncat(str + str_len, buff, strlen(buff));
    str_len += strlen(buff);

    for (size_t i = 0; i < matrix_get_height(self); ++i) {
        for (size_t j = 0; j < matrix_get_width(self); ++j) {
            char* value_str = self->type->to_string(err, matrix_get_value(err, self, i, j));
            snprintf(buff, 256, "%s", value_str);
            free(value_str);
            strncat(str + str_len, buff, strlen(buff));
            str_len += strlen(buff);

            strcat(str + str_len, " ");
            str_len++;
        }
        strcat(str + str_len, "\n");
        str_len++;
    }
    free(buff);

    str = realloc(str, sizeof(char) * (strlen(str) + 1));
    if (str == NULL) {
        error_raise(err, "can't allocate memory");
        return NULL;
    }
    return str;
}

void matrix_print(error* err, matrix_t* self) {
    char* str = matrix_to_string(err, self);
    printf("%s", str);
    free(str);
}
