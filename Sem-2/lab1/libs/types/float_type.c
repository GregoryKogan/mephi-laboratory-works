//
// Created by Gregory Kogan on 07.03.2023.
//

#include "float_type.h"

void* float_get_zero() {
    float* zero = (float*)malloc(sizeof(float));
    if (zero == NULL)
        log_error_and_exit("can't allocate memory", 3);
    *zero = (float)0.0;
    return (void*)zero;
}

void* float_get_one() {
    float* one = (float*)malloc(sizeof(float));
    if (one == NULL)
        log_error_and_exit("can't allocate memory", 3);
    *one = (float)1.0;
    return (void*)one;
}

void* float_from_instance(const void* instance_ptr) {
    float instance = *(float*)instance_ptr;
    float* new_instance_ptr = (float*)malloc(sizeof(float));
    if (new_instance_ptr == NULL)
        log_error_and_exit("can't allocate memory", 3);
    *new_instance_ptr = instance;
    return (void*)new_instance_ptr;
}

void float_free_memory(void* instance_ptr) {
    free(instance_ptr);
}

void float_add(void* res_ptr, void* a_ptr, void* b_ptr) {
    float* res = (float*)res_ptr;
    float* a = (float*)a_ptr;
    float* b = (float*)b_ptr;
    float res_val = *a + *b;
    *res = res_val;
}

void float_sub(void* res_ptr, void* a_ptr, void* b_ptr) {
    float* res = (float*)res_ptr;
    float* a = (float*)a_ptr;
    float* b = (float*)b_ptr;
    float res_val = *a - *b;
    *res = res_val;
}

void float_mul(void* res_ptr, void* a_ptr, void* b_ptr) {
    float* res = (float*)res_ptr;
    float* a = (float*)a_ptr;
    float* b = (float*)b_ptr;
    float res_val = *a * *b;
    *res = res_val;
}

char* float_to_string(void* x_ptr) {
    float x = *(float*)x_ptr;
    char* buff = (char*)malloc(sizeof(char) * 16);
    if (buff == NULL)
        log_error_and_exit("can't allocate memory", 3);
    snprintf(buff, 16, "%.2f", x);
    return buff;
}

type_t* float_type_ctor() {
    return type_ctor(
            "float",
            float_get_zero(),
            float_get_one(),
            float_from_instance,
            float_free_memory,
            float_add,
            float_sub,
            float_mul,
            float_to_string
    );
}
