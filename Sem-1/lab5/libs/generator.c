#include "arraylib.h"
#include "carlib.h"
#include "logger.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MODEL_CHARSET "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ- "
#define OWNER_CHARSET                                                          \
  "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789.-#'?! "

char *randString(size_t len, const char charset[]) {
  char *str = calloc(len + 1, sizeof(char));
  if (str == NULL)
    logErrorAndExit("can not allocate memory", 2);

  for (size_t i = 0; i < len; ++i) {
    int key = rand() % strlen(charset);
    str[i] = charset[key];
  }
  str[len] = '\0';

  return str;
}

void generateDataToFile(char filename[], size_t itemCount) {
  FILE *fptr = fopen(filename, "w");
  if (fptr == NULL)
    logErrorAndExit("can not open file", 3);

  fprintf(fptr, "model,owner,mileage\n");
  for (size_t i = 0; i < itemCount; ++i) {
    size_t modelLen = rand() % 16 + 1;
    size_t ownerLen = rand() % 32 + 1;
    char *model = randString(modelLen, MODEL_CHARSET);
    char *owner = randString(ownerLen, OWNER_CHARSET);
    float mileage = (float)rand() / (float)(RAND_MAX / 10000.0);
    fprintf(fptr, "%s,%s,%f\n", model, owner, mileage);
    free(model);
    free(owner);
  }
  fclose(fptr);
}

array generateData(size_t itemCount) {
  array arr = initArray();

  for (size_t i = 0; i < itemCount; ++i) {
    size_t modelLen = rand() % 16 + 1;
    size_t ownerLen = rand() % 32 + 1;
    char *model = randString(modelLen, MODEL_CHARSET);
    char *owner = randString(ownerLen, OWNER_CHARSET);
    float mileage = (float)rand() / (float)(RAND_MAX / 10000.0);

    car c = createCar(model, owner, mileage);
    append(&arr, c);

    free(model);
    free(owner);
  }

  return arr;
}
