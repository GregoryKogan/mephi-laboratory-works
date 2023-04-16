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
void error_dtor(error*);
void error_raise(error*, char*);

#endif //LAB1_ERROR_H
