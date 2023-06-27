//
// Created by Gregory Kogan on 26.02.2023.
//

#ifndef LAB1_LOGGER_H
#define LAB1_LOGGER_H

#include "../Errors/error.h"
#include <stdio.h>
#include <stdlib.h>

void log_red(char str[]);
void log_green(char str[]);
void log_error(error *err);
void log_fatal_error(error *err);

#endif // LAB1_LOGGER_H
