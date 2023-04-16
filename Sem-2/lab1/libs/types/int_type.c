//
// Created by Gregory Kogan on 26.02.2023.
//

#include "int_type.h"

void* int_get_zero(error* err) {
    int* zero = (int*)malloc(sizeof(int));
    if (zero == NULL) {
        error_raise(err, "can't allocate memory");
        return NULL;
    }
    *zero = (int)0;
    return (void*)zero;
}

void* int_get_one(error* err) {
    int* one = (int*)malloc(sizeof(int));
    if (one == NULL) {
        error_raise(err, "can't allocate memory");
        return NULL;
    }
    *one = (int)1;
    return (void*)one;
}

void* int_from_instance(error* err, const void* instance_ptr) {
    int instance = *(int*)instance_ptr;
    int* new_instance_ptr = (int*)malloc(sizeof(int));
    if (new_instance_ptr == NULL) {
        error_raise(err, "can't allocate memory");
        return NULL;
    }
    *new_instance_ptr = instance;
    return (void*)new_instance_ptr;
}

void int_free_memory(void* instance_ptr) {
    free(instance_ptr);
}

void int_add(void* res_ptr, void* a_ptr, void* b_ptr) {
    int* res = (int*)res_ptr;
    int* a = (int*)a_ptr;
    int* b = (int*)b_ptr;
    int res_val = *a + *b;
    *res = res_val;
}

void int_sub(void* res_ptr, void* a_ptr, void* b_ptr) {
    int* res = (int*)res_ptr;
    int* a = (int*)a_ptr;
    int* b = (int*)b_ptr;
    int res_val = *a - *b;
    *res = res_val;
}

void int_mul(void* res_ptr, void* a_ptr, void* b_ptr) {
    int* res = (int*)res_ptr;
    int* a = (int*)a_ptr;
    int* b = (int*)b_ptr;
    int res_val = *a * *b;
    *res = res_val;
}

char* int_to_string(error* err, void* x_ptr) {
    int x = *(int*)x_ptr;
    char* buff = (char*)malloc(sizeof(char) * 16);
    if (buff == NULL) {
        error_raise(err, "can't allocate memory");
        return NULL;
    }
    snprintf(buff, 16, "%d", x);
    return buff;
}

type_t* int_type_ctor(error* err) {
    return type_ctor(
            err,
            "int",
            int_get_zero(err),
            int_get_one(err),
            int_from_instance,
            int_free_memory,
            int_add,
            int_sub,
            int_mul,
            int_to_string
    );
}
