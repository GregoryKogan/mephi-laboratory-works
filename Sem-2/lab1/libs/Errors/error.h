//
// Created by Gregory Kogan on 16.04.2023.
//

#ifndef LAB1_ERROR_H
#define LAB1_ERROR_H

#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

typedef struct Error {
    char* message;
    bool raised;
} error;

error* error_ctor(void);
void error_dtor(error* self);
void error_raise(error* self, char*);
void error_clear(error* self);

#endif //LAB1_ERROR_H
