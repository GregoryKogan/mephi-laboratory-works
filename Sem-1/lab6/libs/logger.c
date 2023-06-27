#include <stdio.h>
#include <stdlib.h>
#define RED "\x1b[31m"
#define YELLOW "\x1b[33m"
#define GREEN "\x1b[32m"
#define END "\x1b[0m"

void logError(char err[]) { fprintf(stderr, RED "Error: %s" END "\n", err); }

void logErrorAndExit(char err[], int status) {
  fprintf(stderr, RED "Error: %s" END "\n", err);
  exit(status);
}

void logWarning(char warning[]) {
  fprintf(stderr, YELLOW "Warning: %s" END "\n", warning);
}

void logSuccess(char success[]) { printf(GREEN "%s" END "\n", success); }
