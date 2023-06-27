//
// Created by Gregory Kogan on 17.04.2023.
//

#ifndef LAB1_MENUS_H
#define LAB1_MENUS_H

#include "../matrix.h"
#include <stdio.h>
#include <stdlib.h>

int main_menu(void);
void go_back();
int select_type_menu(void);
int select_fill_menu(void);
void *type_scan(error *err, type_t *t);
void manual_fill_menu(error *, matrix_t *);
matrix_t *create_matrix(error *err);
void transpose_menu(error *err);
void add_matrix_to_matrix_menu(error *err);
void add_scalar_to_matrix_menu(error *err);
void multiply_matrices_menu(error *err);
void multiply_matrix_by_scalar_menu(error *err);
void linear_combination_of_rows_menu(error *err);

#endif // LAB1_MENUS_H
