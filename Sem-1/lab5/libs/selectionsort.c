#include "arraylib.h"
#include "carlib.h"
#include "cmpfunctions.h"
#include <stdbool.h>
#include <stdlib.h>
#include <strings.h>

void selectionSort(car *arr, size_t len, size_t elemSize,
                   int (*cmpFunc)(const car *, const car *)) {
  int minIndex;
  for (int i = 0; i < len - 1; ++i) {
    minIndex = i;
    for (int j = i + 1; j < len; ++j) {
      if (cmpFunc(&arr[j], &arr[minIndex]) < 0)
        minIndex = j;
    }
    if (minIndex != i) {
      car tmp = arr[i];
      arr[i] = arr[minIndex];
      arr[minIndex] = tmp;
    }
  }
}

void selectionSortCars(array *cars, int ascendingOrder, char sortingField) {
  if (ascendingOrder == 1) {
    if (sortingField == 'a')
      selectionSort(cars->data, cars->length, sizeof(car),
                    (int (*)(const car *, const car *))compareAscMileage);
    else if (sortingField == 'm')
      selectionSort(cars->data, cars->length, sizeof(car),
                    (int (*)(const car *, const car *))compareAscModel);
    else
      selectionSort(cars->data, cars->length, sizeof(car),
                    (int (*)(const car *, const car *))compareAscOwner);
  } else {
    if (sortingField == 'a')
      selectionSort(cars->data, cars->length, sizeof(car),
                    (int (*)(const car *, const car *))compareDesMileage);
    else if (sortingField == 'm')
      selectionSort(cars->data, cars->length, sizeof(car),
                    (int (*)(const car *, const car *))compareDesModel);
    else
      selectionSort(cars->data, cars->length, sizeof(car),
                    (int (*)(const car *, const car *))compareDesOwner);
  }
}
