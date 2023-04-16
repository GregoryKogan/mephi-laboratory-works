//
// Created by Gregory Kogan on 16.04.2023.
//

#include "error.h"

error* error_ctor() {
    error* e = malloc(sizeof(error));
    e->raised = false;
    e->message = NULL;
    return e;
}

void error_dtor(error* self) {
    free(self);
}

void error_raise(error* self, char* msg) {
    self->message = msg;
    self->raised = true;
}
