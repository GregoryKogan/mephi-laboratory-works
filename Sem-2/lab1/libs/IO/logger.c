//
// Created by Gregory Kogan on 26.02.2023.
//

#include "logger.h"

#define RED "\x1b[31m"
#define GREEN "\x1b[32m"
#define END "\x1b[0m"

void log_red(char str[]) { printf(RED "%s" END, str); }

void log_green(char str[]) { printf(GREEN "%s" END, str); }

void log_error(error *err) { printf(RED "Error: %s" END "\n", err->message); }

void log_fatal_error(error *err) {
  printf(RED "Error: %s" END "\n", err->message);
  exit(1);
}
