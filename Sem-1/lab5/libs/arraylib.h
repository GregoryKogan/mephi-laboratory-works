#ifndef ARRAYS_H
#define ARRAYS_H

#include "carlib.h"
typedef struct Array {
  size_t length;
  car *data;
} array;
array initArray();
void arrayMemoryFree(array *arr);
void printArray(array *arr);
void removeByIndex(array *arr, int index);
void append(array *arr, car value);

#endif
