#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>


typedef struct Array {
    int length;
    int* data;
} array;


array initArray() {
    array arr = {0, NULL};
    return arr;
}

void freeMemory(array* arr) {
    free(arr->data);
    arr->length = 0;
    arr->data = NULL;
}

void print(array* arr) {
    if (arr->length == 0) {
        printf("[]\n");
        return;
    }
    printf("[%d", arr->data[0]);
    for (int i = 1; i < arr->length; i++)
        printf(", %d", arr->data[i]);
    printf("]\n");
}

void insert(array* arr, int index, int value) {
    int newSpace = 1;
    if (index >= arr->length)
        newSpace = index - arr->length + 1;

    if (arr->length == 0)
        arr->data = calloc(newSpace, sizeof(int));
    else
        arr->data = realloc(arr->data, (arr->length + newSpace) * sizeof(int));
    if (!arr->data) {
        printf("Error1: failed to allocate memory\n");
        exit(-1);
    }

    for (int i = 0; i < newSpace; ++i)
        arr->data[arr->length + i] = 0;

    arr->length += newSpace;
    for (int i = arr->length - 1; i > index; i--)
        arr->data[i] = arr->data[i - 1];
    arr->data[index] = value;
}

void removeByIndex(array* arr, int index) {
    for (int i = index; i < arr->length - 1; i++)
        arr->data[i] = arr->data[i + 1];
    if (arr->length - 1 > 0) {
    	arr->data = realloc(arr->data, (arr->length - 1) * sizeof(int));
        if (!arr->data) {
	    printf("Error2: failed to allocate memory\n");
            exit(-1);
	}
	arr->length--;
    }
    else
	freeMemory(arr);
}

void dialogInput(array* arr) {
    freeMemory(arr);
    printf("=-=-= Array Dialog Input =-=-=\n");
    printf("'+' - Add element\n");
    printf("Input '<index> <value>' (<value> can't be 0!)\n");
    printf("'-' - Remove element\n");
    printf("Input '<index>'\n");
    printf("To end input press 'Ctrl+D'\n");

    char cmd;
    int index, value;
    int status;
    while (true) {
        printf("Operation [+, -]: ");
        status = scanf(" %c", &cmd);
        if (status == EOF) break;
        if (status != 1) {
            printf("Error: invalid input\n");
            continue;
        }
        if (cmd != '+' && cmd != '-') {
            printf("Error: command must be '+' or '-'\n");
            continue;
        }

        if (cmd == '+') {
            printf("<index> <value>: ");
            status = scanf("%d %d", &index, &value);
            if (status == EOF) break;
            if (status != 2) {
                printf("Error: invalid input\n");
                continue;
            }
            if (index < 0 || value == 0) {
                printf("Error: index can't be negative and value can't be equal to zero\n");
                continue;
            }

            if (index < arr->length && arr->data[index] == 0)
                arr->data[index] = value;
            else
                insert(arr, index, value);
        } else {
            printf("<index>: ");
            status = scanf("%d", &index);
            if (status == EOF) break;
            if (status != 1) {
                printf("Error: invalid input\n");
                continue;
            }
            if (index < 0 || index >= arr->length) {
                printf("Error: index can't be negative or larger than array's length\n");
                continue;
            }
            removeByIndex(arr, index);
        }

        print(arr);
    }

    printf("\nYour array: \n");
    print(arr);
}
