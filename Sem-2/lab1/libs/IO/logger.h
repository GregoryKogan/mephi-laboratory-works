//
// Created by Gregory Kogan on 26.02.2023.
//

#ifndef LAB1_LOGGER_H
#define LAB1_LOGGER_H

#include <stdio.h>
#include <stdlib.h>

void log_error(char err[]);
void log_error_and_exit(char err[], int status);
void log_warning(char warning[]);
void log_success(char success[]);

#endif //LAB1_LOGGER_H
