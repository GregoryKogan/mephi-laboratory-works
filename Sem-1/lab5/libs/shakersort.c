#include "arraylib.h"
#include "carlib.h"
#include "cmpfunctions.h"
#include <stdbool.h>
#include <stdlib.h>
#include <strings.h>

void shakerSort(car *arr, size_t len, size_t elemSize,
                int (*cmpFunc)(const car *, const car *)) {
  bool swapped = true;
  int start = 0;
  int end = len - 1;

  while (swapped) {
    swapped = false;

    for (int i = start; i < end; i++) {
      if (cmpFunc(&arr[i], &arr[i + 1]) > 0) {
        car tmp = arr[i];
        arr[i] = arr[i + 1];
        arr[i + 1] = tmp;
        swapped = true;
      }
    }

    if (!swapped)
      break;

    swapped = false;
    --end;

    for (int i = end - 1; i >= start; --i) {
      if (cmpFunc(&arr[i], &arr[i + 1]) > 0) {
        car tmp = arr[i];
        arr[i] = arr[i + 1];
        arr[i + 1] = tmp;
        swapped = true;
      }
    }

    ++start;
  }
}

void shakerSortCars(array *cars, int ascendingOrder, char sortingField) {
  if (ascendingOrder == 1) {
    if (sortingField == 'a')
      shakerSort(cars->data, cars->length, sizeof(car),
                 (int (*)(const car *, const car *))compareAscMileage);
    else if (sortingField == 'm')
      shakerSort(cars->data, cars->length, sizeof(car),
                 (int (*)(const car *, const car *))compareAscModel);
    else
      shakerSort(cars->data, cars->length, sizeof(car),
                 (int (*)(const car *, const car *))compareAscOwner);
  } else {
    if (sortingField == 'a')
      shakerSort(cars->data, cars->length, sizeof(car),
                 (int (*)(const car *, const car *))compareDesMileage);
    else if (sortingField == 'm')
      shakerSort(cars->data, cars->length, sizeof(car),
                 (int (*)(const car *, const car *))compareDesModel);
    else
      shakerSort(cars->data, cars->length, sizeof(car),
                 (int (*)(const car *, const car *))compareDesOwner);
  }
}
