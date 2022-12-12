#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "carlib.h"
#include "logger.h"


typedef struct Array {
    int length;
    car* data;
} array;


array initArray() {
    array arr = {0, NULL};
    return arr;
}

void arrayMemoryFree(array* arr) {
    for (size_t i = 0; i < arr->length; i++)
        carMemoryFree(arr->data[i]);
    free(arr->data);
    arr->length = 0;
    arr->data = NULL;
}

void printArray(array* arr) {
    if (arr->length == 0) {
        printf("[]\n");
        return;
    }
    printf("[\n");
    for (int i = 0; i < arr->length; i++) {
        printf("\t");
        printCar(arr->data[i]);
        printf(",\n");
    }
    printf("]\n");
}

void insert(array* arr, int index, car value) {
    int newSpace = 1;
    if (index >= arr->length)
        newSpace = index - arr->length + 1;

    if (arr->length == 0)
        arr->data = calloc(newSpace, sizeof(car));
    else
        arr->data = realloc(arr->data, (arr->length + newSpace) * sizeof(car));
    if (!arr->data)
        logErrorAndExit("can not allocate memory", 2);

    for (int i = 0; i < newSpace; ++i)
        arr->data[arr->length + i] = createCar("", "", 0);

    arr->length += newSpace;
    for (int i = arr->length - 1; i > index; i--)
        arr->data[i] = arr->data[i - 1];
    arr->data[index] = value;
}

void append(array* arr, car value) {
    insert(arr, arr->length, value);
}

void removeByIndex(array* arr, int index) {
    for (int i = index; i < arr->length - 1; i++)
        arr->data[i] = arr->data[i + 1];
    if (arr->length - 1 > 0) {
    	arr->data = realloc(arr->data, (arr->length - 1) * sizeof(car));
        if (!arr->data)
           logErrorAndExit("can not allocate memory", 2);
        arr->length--;
    }
    else
	    arrayMemoryFree(arr);
}
