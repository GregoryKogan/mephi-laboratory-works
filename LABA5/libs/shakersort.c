#include <stdlib.h>
#include <stdbool.h>
#include <strings.h>
#include "carlib.h"
#include "arraylib.h"
#include "cmpfunctions.h"


void shakerSort(car* arr, size_t len, size_t elemSize, int (*cmpFunc)(const car*, const car*)) {
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

        if (!swapped) break;

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


void shakerSortCars(array* cars, int ascendingOrder, char sortingField) {
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