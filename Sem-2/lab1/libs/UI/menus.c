//
// Created by Gregory Kogan on 17.04.2023.
//

#include "menus.h"
#include "../IO/logger.h"
#include "../types/int_type.h"
#include "../types/float_type.h"


int main_menu(void) {
    log_green("Choose action:\n");
    printf("1 - exit program\n");
    printf("2 - transpose matrix\n");
    printf("3 - add matrix to another matrix\n");
    printf("4 - add scalar to matrix\n");
    printf("5 - multiply two matrices\n");
    printf("6 - multiply matrix by scalar\n");
    printf("7 - linear combination or rows\n");
    int action;
    printf(">>> ");
    int status = scanf("%d", &action);
    fflush(stdin);
    if (!status) return -1;
    return action;
}

void go_back() {
    log_green("\nPress ENTER to go back");
    int c;
    while ((c = getchar()) != '\n' && c != EOF) { }
    getchar();
}

int select_type_menu() {
    log_green("Select type\n");
    printf("1 - int\n");
    printf("2 - float\n");
    int action = 0;
    while (1) {
        printf(">>> ");
        scanf("%d", &action);
        fflush(stdin);
        if (action == 1 || action == 2)
            return action;
        else
            log_red("invalid action!\n");
    }
}

int select_fill_menu(void) {
    log_green("Select fill method\n");
    printf("1 - all zeros\n");
    printf("2 - all ones\n");
    printf("3 - random\n");
    printf("4 - manual\n");
    int method = 0;
    while (1) {
        printf(">>> ");
        scanf("%d", &method);
        fflush(stdin);
        if (method >= 1 && method <= 4)
            return method;
        else
            log_red("invalid method!\n");
    }
}

void* type_scan(error* err, type_t* t) {
    int status;
    if (strcmp(t->name, "int") == 0) {
        int value;
        status = scanf("%d", &value);
        fflush(stdin);
        if (status != 1) {
            error_raise(err, "invalid value");
            return NULL;
        }
        return t->from_instance(err, &value);
    } else if (strcmp(t->name, "float") == 0) {
        float value;
        status = scanf("%f", &value);
        fflush(stdin);
        if (status != 1) {
            error_raise(err, "invalid value");
            return NULL;
        }
        return t->from_instance(err, &value);
    } else {
        error_raise(err, "unknown type name");
        return NULL;
    }
}

void manual_fill_menu(error* err, matrix_t* m) {
    log_green("Manual fill\n");
    for (size_t i = 0; i < matrix_get_height(m); ++i) {
        for (size_t j = 0; j < matrix_get_width(m); ++j) {
            printf("matrix[%zu][%zu] = ", i, j);
            void* value = type_scan(err, m->type);
            if (err->raised) return;
            matrix_set_value(err, m, i, j, value);
            m->type->free_memory(value);
            if (err->raised) return;
        }
    }
}

matrix_t* create_matrix(error* err) {
    log_green("Create matrix\n");

    int type_num = select_type_menu();
    type_t* type;
    if (type_num == 1) type = int_type_ctor(err);
    else type = float_type_ctor(err);
    if (err->raised) {
        type_dtor(type);
        return NULL;
    }

    int status;
    int height, width;
    printf("Matrix height: ");
    status = scanf("%d", &height);
    if (status != 1 || height <= 0) {
        error_raise(err, "invalid matrix height");
        type_dtor(type);
        return NULL;
    }
    printf("Matrix width: ");
    status = scanf("%d", &width);
    if (status != 1 || width <= 0) {
        error_raise(err, "invalid matrix width");
        type_dtor(type);
        return NULL;
    }

    matrix_t* m = matrix_ctor(err, type, (size_t)height, (size_t)width);
    if (err->raised) {
        matrix_dtor(m);
        type_dtor(type);
        return NULL;
    }

    int fill_method_num = select_fill_menu();
    if (fill_method_num == 2)
        matrix_fill(err, m, m->type->one);
    else if (fill_method_num == 3)
        matrix_random_fill(err, m);
    else if (fill_method_num == 4)
        manual_fill_menu(err, m);

    if (err->raised) {
        matrix_dtor(m);
        return NULL;
    }

    log_green("Your matrix:\n");
    matrix_print(err, m);
    if (err->raised) {
        matrix_dtor(m);
        return NULL;
    }

    return m;
}

void transpose_menu(error* err) {
    log_green("Matrix transposition\n");
    matrix_t* m = create_matrix(err);
    if (err->raised) {
        matrix_dtor(m);
        return;
    }
    matrix_t* t = matrix_transpose(err, m);
    if (err->raised) return;
    log_green("Transposed matrix: \n");
    matrix_print(err, t);
    matrix_dtor(m);
    matrix_dtor(t);
    if (err->raised) return;
    go_back();
}

void add_matrix_to_matrix_menu(error* err) {
    log_green("Add matrix to another matrix\n");

    matrix_t* matrix_a = create_matrix(err);
    if (err->raised) {
        matrix_dtor(matrix_a);
        return;
    }

    matrix_t* matrix_b = create_matrix(err);
    if (err->raised) {
        matrix_dtor(matrix_a);
        matrix_dtor(matrix_b);
        return;
    }

    matrix_t* result = matrix_add(err, matrix_a, matrix_b);
    if (err->raised) {
        matrix_dtor(matrix_a);
        matrix_dtor(matrix_b);
        matrix_dtor(result);
        return;
    }

    log_green("Matrix A: \n");
    matrix_print(err, matrix_a);
    log_green("Matrix B: \n");
    matrix_print(err, matrix_b);
    log_green("Sum of matrices: \n");
    matrix_print(err, result);
    matrix_dtor(matrix_a);
    matrix_dtor(matrix_b);
    matrix_dtor(result);
    if (err->raised) return;
    go_back();
}

void add_scalar_to_matrix_menu(error* err) {
    log_green("Add scalar to matrix\n");

    matrix_t* m = create_matrix(err);
    if (err->raised) {
        matrix_dtor(m);
        return;
    }

    printf("scalar = ");
    void* alpha = type_scan(err, m->type);
    if (err->raised) {
        m->type->free_memory(alpha);
        matrix_dtor(m);
        return;
    }

    matrix_t* result = matrix_add_scalar(err, m, alpha);
    if (err->raised) {
        m->type->free_memory(alpha);
        matrix_dtor(m);
        matrix_dtor(result);
    }

    log_green("Sum of matrix and scalar: \n");
    matrix_print(err, result);
    m->type->free_memory(alpha);
    matrix_dtor(m);
    matrix_dtor(result);
    if (err->raised) return;

    go_back();
}

void multiply_matrices_menu(error* err) {
    log_green("Multiply two matrices\n");

    matrix_t* matrix_a = create_matrix(err);
    if (err->raised) {
        matrix_dtor(matrix_a);
        return;
    }

    matrix_t* matrix_b = create_matrix(err);
    if (err->raised) {
        matrix_dtor(matrix_a);
        matrix_dtor(matrix_b);
        return;
    }

    matrix_t* result = matrix_mul(err, matrix_a, matrix_b);
    if (err->raised) {
        matrix_dtor(matrix_a);
        matrix_dtor(matrix_b);
        matrix_dtor(result);
        return;
    }

    log_green("Matrix A: \n");
    matrix_print(err, matrix_a);
    log_green("Matrix B: \n");
    matrix_print(err, matrix_b);
    log_green("Multiplication of matrices: \n");
    matrix_print(err, result);
    matrix_dtor(matrix_a);
    matrix_dtor(matrix_b);
    matrix_dtor(result);
    if (err->raised) return;

    go_back();
}

void multiply_matrix_by_scalar_menu(error* err) {
    log_green("Multiply matrix by scalar\n");

    matrix_t* m = create_matrix(err);
    if (err->raised) {
        matrix_dtor(m);
        return;
    }

    printf("scalar = ");
    void* alpha = type_scan(err, m->type);
    if (err->raised) {
        m->type->free_memory(alpha);
        matrix_dtor(m);
        return;
    }

    matrix_t* result = matrix_mul_scalar(err, m, alpha);
    if (err->raised) {
        m->type->free_memory(alpha);
        matrix_dtor(m);
        matrix_dtor(result);
    }

    log_green("Multiplication of matrix and scalar: \n");
    matrix_print(err, result);
    m->type->free_memory(alpha);
    matrix_dtor(m);
    matrix_dtor(result);
    if (err->raised) return;

    go_back();
}

void linear_combination_of_rows_menu(error* err) {
    log_green("Linear combination of rows\n");

    matrix_t* m = create_matrix(err);
    if (err->raised) {
        matrix_dtor(m);
        return;
    }

    printf("row index = ");
    size_t row_index;
    if (scanf("%zu", &row_index) != 1)
        error_raise(err, "invalid row index");
    if (row_index >= matrix_get_height(m) || row_index < 0)
        error_raise(err, "row index out of range");
    if (err->raised) {
        matrix_dtor(m);
        return;
    }

    void** alphas = malloc(sizeof(void*) * (matrix_get_height(m) - 1));
    for (size_t i = 0; i < matrix_get_height(m) - 1; ++i) {
        printf("alphas[%zu] = ", i);
        void* alpha = type_scan(err, m->type);
        if (err->raised) {
            for (size_t j = 0; j < i; ++j)
                m->type->free_memory(alphas[j]);
            m->type->free_memory(alpha);
            matrix_dtor(m);
            return;
        }

        alphas[i] = alpha;
    }


    matrix_t* result = matrix_add_linear_combination(err, m, row_index, (const void **) alphas);
    for (size_t i = 0; i < matrix_get_height(m) - 1; ++i)
        m->type->free_memory(alphas[i]);
    free(alphas);

    if (err->raised) {
        matrix_dtor(m);
        return;
    }

    log_green("Linear combination of rows: \n");
    matrix_print(err, result);
    matrix_dtor(m);
    matrix_dtor(result);
    if (err->raised) return;

    go_back();
}
