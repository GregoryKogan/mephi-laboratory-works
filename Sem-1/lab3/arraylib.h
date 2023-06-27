#ifndef FUNCTIONS_H_INCLUDED
#define FUNCTIONS_H_INCLUDED

typedef struct Array {
  int length;
  int *data;
} array;
array initArray();
void freeMemory(array *arr);
void print(array *arr);
void insert(array *arr, int index, int value);
void removeByIndex(array *arr, int index);
void dialogInput(array *arr);

#endif
