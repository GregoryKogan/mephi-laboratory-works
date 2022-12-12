#include <stdlib.h>
#include <stdbool.h>
#include <strings.h>
#include "carlib.h"
#include "arraylib.h"
#include "cmpfunctions.h"


void quickSortCars(array* cars, int ascendingOrder, char sortingField) {
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
