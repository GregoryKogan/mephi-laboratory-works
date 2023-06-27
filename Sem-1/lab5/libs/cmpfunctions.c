#include "arraylib.h"
#include "carlib.h"
#include <stdbool.h>
#include <string.h>
#include <strings.h>

int compareAscMileage(const car *a, const car *b) {
  if (a->mileage < b->mileage)
    return -1;
  if (a->mileage > b->mileage)
    return 1;
  return 0;
}

int compareAscModel(const car *a, const car *b) {
  return strcmp(a->model, b->model);
}

int compareAscOwner(const car *a, const car *b) {
  return strcmp(a->owner, b->owner);
}

int compareDesMileage(const car *a, const car *b) {
  if (b->mileage < a->mileage)
    return -1;
  if (b->mileage > a->mileage)
    return 1;
  return 0;
}

int compareDesModel(const car *a, const car *b) {
  return strcmp(b->model, a->model);
}

int compareDesOwner(const car *a, const car *b) {
  return strcmp(b->owner, a->owner);
}
