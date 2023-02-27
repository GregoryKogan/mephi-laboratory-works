//
// Created by Gregory Kogan on 26.02.2023.
//

#include "int_type.h"

void* int_get_zero() {
    int* zero = (int*)malloc(sizeof(int));
    *zero = (int)0;
    return (void*)zero;
}

void* int_get_one() {
    int* one = (int*)malloc(sizeof(int));
    *one = (int)1;
    return (void*)one;
}

void* int_add(void* a_ptr, void* b_ptr) {
    int* a = (int*)a_ptr;
    int* b = (int*)b_ptr;
    int* res = (int*) malloc(sizeof(int));
    *res = *a + *b;
    return (void*)res;
}

void* int_sub(void* a_ptr, void* b_ptr) {
    int* a = (int*)a_ptr;
    int* b = (int*)b_ptr;
    int* res = (int*) malloc(sizeof(int));
    *res = *a - *b;
    return (void*)res;
}

void* int_mul(void* a_ptr, void* b_ptr) {
    int* a = (int*)a_ptr;
    int* b = (int*)b_ptr;
    int* res = (int*)malloc(sizeof(int));
    *res = *a * *b;
    return (void*)res;
}

char* int_to_string(void* x_ptr) {
    int x = *(int*)x_ptr;
    char* buff = (char*)malloc(sizeof(char) * 16);
    snprintf(buff, 16, "%d", x);
    return buff;
}

type_t* int_type_ctor() {
    return type_ctor(
            sizeof(int),
            int_get_zero(),
            int_get_one(),
            &int_add,
            &int_sub,
            &int_mul,
            &int_to_string
    );
}
