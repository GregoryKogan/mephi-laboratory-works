//
// Created by Gregory Kogan on 26.02.2023.
//

#include "matrix.h"

matrix_t* matrix_ctor(type_t* type, size_t height, size_t width) {
    matrix_t* matrix = (matrix_t *)malloc(sizeof(matrix_t));
    matrix->width = width;
    matrix->height = height;
    matrix->type = type;
    matrix->data = (void**)malloc(width * height * sizeof(void*));
    for (size_t index = 0; index < height * width; ++index)
            matrix->data[index] = type->zero;
    return matrix;
}

void matrix_dtor(matrix_t* self) {
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
    if (i >= self->height || j >= self->width)
        log_error_and_exit("matrix index out of range", 1);
    size_t index = i * self->width + j;
    return self->data[index];
}

void matrix_set_value(matrix_t* self, size_t i, size_t j, void* value) {
    if (i >= self->height || j >= self->width)
        log_error_and_exit("matrix index out of range", 1);
    if (sizeof(value) != self->type->size)
        log_error_and_exit("incompatible type given", 1);

    size_t index = i * self->width + j;
    self->data[index] = value;
}

char* matrix_to_string(matrix_t* self) {
    char* str = (char*)malloc(sizeof(char) * 256);
    str[0] = '\0';
    size_t str_len = 0;
    char* buff = (char*)malloc(sizeof(char) * 256);
    snprintf(buff, 256, "<Matrix [%lu x %lu]>\n", self->height, self->width);
    strncat(str + str_len, buff, strlen(buff));
    str_len += strlen(buff);
    for (size_t i = 0; i < self->height; ++i) {
        if (i == 0) strcat(str + str_len, "[");
        else strcat(str + str_len, " ");
        str_len++;

        char* first_value_str = self->type->to_string(matrix_get_value(self, i, 0));
        snprintf(buff, 256, "%s", first_value_str);
        free(first_value_str);
        strncat(str + str_len, buff, strlen(buff));
        str_len += strlen(buff);
        for (size_t j = 1; j < self->width; ++j) {
            strcat(str + str_len, ", ");
            str_len += 2;
            char* value_str = self->type->to_string(matrix_get_value(self, i, j));
            snprintf(buff, 256, "%s", value_str);
            free(value_str);
            strncat(str + str_len, buff, strlen(buff));
            str_len += strlen(buff);
        }

        if (i == self->height - 1) {
            strcat(str + str_len, "]");
            str_len++;
        }
        strcat(str + str_len, "\n");
        str_len++;
    }

    free(buff);
    return str;
}

void matrix_print(matrix_t* self) {
    char* str = matrix_to_string(self);
    printf("%s", str);
    free(str);
}
