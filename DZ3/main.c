#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>


typedef struct Array {
    int length;
    int* data;
} array;


array initArray();
void freeMemory(array* arr);
void print(array* arr);
void insert(array* arr, int index, int value);
void dialogInput(array* arr);
void removeDuplicatesInLinearTime(array* arr);


int main() {
    array arr = initArray();
    dialogInput(&arr);
    removeDuplicatesInLinearTime(&arr);
    printf("Removed duplicates:\n");
    print(&arr);
    freeMemory(&arr);
    return 0;
}


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
        printf("Error: failed to allocate memory\n");
        exit(-1);
    }

    for (int i = 0; i < newSpace; ++i)
        arr->data[arr->length + i] = 0;

    arr->length += newSpace;

    for (int i = arr->length - 1; i > index; i--)
        arr->data[i] = arr->data[i - 1];
    arr->data[index] = value;
}

void dialogInput(array* arr) {
    freeMemory(arr);
    printf("=-=-= Array Dialog Input =-=-=\n");
    printf("Input '<index> <value>' pairs\n");
    printf("<value> can't be 0!\n");
    printf("For example, to insert 5 at index 3 input '3 5'\n");
    printf("To end input press 'Ctrl+D'\n");

    int index, value;
    while (true) {
        int status = scanf("%d %d", &index, &value);
        if (status == EOF) break;
        if (status != 2 || index < 0 || value == 0) {
            printf("Error: invalid input\n");
            exit(-2);
        }

        if (index < arr->length && arr->data[index] == 0)
            arr->data[index] = value;
        else
            insert(arr, index, value);

        print(arr);
    }
}


void removeDuplicatesInLinearTime(array* arr) {
    if (arr->length == 0) return;
    int maxVal = arr->data[0];
    int minVal = arr->data[0];
    for (int i = 1; i < arr->length; ++i) {
        if (arr->data[i] > maxVal)
            maxVal = arr->data[i];
        if (arr->data[i] < minVal)
            minVal = arr->data[i];
    }

    array resArr = initArray();

    int setSize = maxVal - minVal + 1;
    bool* mySet = calloc(setSize, sizeof(bool));
    if (!mySet) {
        printf("Error: failed to allocate memory\n");
        exit(-1);
    }

    for (int i = 0; i < arr->length; ++i) {
        int setInd = arr->data[i] - minVal;
        if (!mySet[setInd])
            insert(&resArr, resArr.length, arr->data[i]);
        mySet[setInd] = true;
    }

    free(mySet);
    freeMemory(arr);
    arr->data = resArr.data;
    arr->length = resArr.length;
}
