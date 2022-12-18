#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "carlib.h"
#include "logger.h"


typedef struct Array {
    size_t length;
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

void append(array* arr, car value) {
    if (arr->length == 0)
        arr->data = calloc(1, sizeof(car));
    else
        arr->data = realloc(arr->data, (arr->length + 1) * sizeof(car));
    if (!arr->data)
        logErrorAndExit("can not allocate memory", 2);
    arr->length++;
    arr->data[arr->length - 1] = value;
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
