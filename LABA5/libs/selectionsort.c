#include <stdlib.h>
#include <stdbool.h>
#include <strings.h>
#include "carlib.h"
#include "arraylib.h"
#include "cmpfunctions.h"


void selectionSort(car* arr, size_t len, size_t elemSize, int (*cmpFunc)(const car*, const car*)) {
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


void selectionSortCars(array* cars, int ascendingOrder, char sortingField) {
    if (ascendingOrder == 1) {
        if (sortingField == 'a')
            qsort(cars->data, cars->length, sizeof(car), (int (*)(const void*, const void*)) compareAscMileage);
        else if (sortingField == 'm')
            qsort(cars->data, cars->length, sizeof(car), (int (*)(const void*, const void*)) compareAscModel);
        else
            qsort(cars->data, cars->length, sizeof(car), (int (*)(const void*, const void*)) compareAscOwner);
    } else {
        if (sortingField == 'a')
            qsort(cars->data, cars->length, sizeof(car), (int (*)(const void*, const void*)) compareDesMileage);
        else if (sortingField == 'm')
            qsort(cars->data, cars->length, sizeof(car), (int (*)(const void*, const void*)) compareDesModel);
        else
            qsort(cars->data, cars->length, sizeof(car), (int (*)(const void*, const void*)) compareDesOwner);
    }
}
