//
// Created by Gregory Kogan on 26.02.2023.
//

#include "matrix.h"

matrix_t* matrix_ctor(type_t* type, size_t height, size_t width) {
    matrix_t* matrix = (matrix_t *)malloc(sizeof(matrix_t));
    if (matrix == NULL)
        log_error_and_exit("can't allocate memory", 3);
    matrix->width = width;
    matrix->height = height;
    matrix->type = type;
    matrix->data = (void**)malloc(width * height * sizeof(void*));
    if (matrix->data == NULL)
        log_error_and_exit("can't allocate memory", 3);
    for (size_t index = 0; index < height * width; ++index)
            matrix->data[index] = matrix->type->from_instance(matrix->type->zero);
    return matrix;
}

void matrix_dtor(matrix_t* self) {
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

void* matrix_get_value(matrix_t* self, size_t i, size_t j) {
    if (i >= matrix_get_height(self) || j >= matrix_get_width(self))
        log_error_and_exit("matrix index out of range", 1);
    size_t index = i * matrix_get_width(self) + j;
    return self->data[index];
}

void matrix_set_value(matrix_t* self, size_t i, size_t j, const void* value) {
    if (i >= matrix_get_height(self) || j >= matrix_get_width(self))
        log_error_and_exit("matrix index out of range", 1);

    size_t index = i * matrix_get_width(self) + j;
    if (self->data[index] != NULL)
        self->type->free_memory(self->data[index]);
    self->data[index] = self->type->from_instance(value);
}

matrix_t* matrix_transpose(matrix_t* self) {
    matrix_t* result = matrix_ctor(type_copy(self->type), matrix_get_width(self), matrix_get_height(self));
    for (size_t j = 0; j < matrix_get_width(self); ++j) {
        for (size_t i = 0; i < matrix_get_height(self); ++i)
            matrix_set_value(result, j, i, matrix_get_value(self, i, j));

    }
    return result;
}

char* matrix_to_string(matrix_t* self) {
    // multiplication by 3 because each element takes 3 chars on average: "8, "
    char* str = (char*)malloc(sizeof(char) * matrix_get_width(self) * matrix_get_height(self) * 3 + 128);
    char* buff = (char*)malloc(sizeof(char) * 256);
    if (str == NULL || buff == NULL)
        log_error_and_exit("can't allocate memory", 3);
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
            char* value_str = self->type->to_string(matrix_get_value(self, i, j));
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
    if (str == NULL)
        log_error_and_exit("can't allocate memory", 3);
    return str;
}

void matrix_print(matrix_t* self) {
    char* str = matrix_to_string(self);
    printf("%s", str);
    free(str);
}
