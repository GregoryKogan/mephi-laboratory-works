//
// Created by Gregory Kogan on 26.02.2023.
//

#include "logger.h"

#define RED "\x1b[31m"
#define YELLOW "\x1b[33m"
#define GREEN "\x1b[32m"
#define END "\x1b[0m"


void log_error(char err[]){
    fprintf(stderr, RED "Error: %s" END "\n", err);
}


void red_print(char str[]) {
    printf(RED "%s" END, str);
}


void log_error_and_exit(char err[], int status){
    fprintf(stderr, RED "Error: %s" END "\n", err);
    exit(status);
}


void log_warning(char warning[]){
    fprintf(stderr, YELLOW "Warning: %s" END "\n", warning);
}


void log_success(char success[]) {
    printf(GREEN "%s" END "\n", success);
}

void green_print(char str[]) {
    printf(GREEN "%s" END, str);
}
