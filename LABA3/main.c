#include "arraylib.h"
#include <stdbool.h>
#include <stdio.h>


bool isProgression(int n) {
    if (n < 0) n *= -1;
    if (n < 100) return true;
    int d1 = n % 10; n /= 10;
    int d2 = n % 10; n /= 10;
    int step = d1 - d2;
    while (n) {
        int d = n % 10; n /= 10;
        if (d2 - d != step) return false;
        d2 = d;
    }
    return true;
}


int main() {
    array arr = initArray();
    dialogInput(&arr);

    array resArr = initArray();
    for (int i = 0; i < arr.length; i++) {
        if (isProgression(arr.data[i])) {
            insert(&resArr, resArr.length, arr.data[i]);
            removeByIndex(&arr, i);
            i--;
        }
    }

    printf("Inital array without progressions: \n");
    print(&arr);
    printf("Result array with progressions: \n");
    print(&resArr);

    freeMemory(&arr);
    freeMemory(&resArr);
    return 0;
}
