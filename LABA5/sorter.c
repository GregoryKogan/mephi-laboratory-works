#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <unistd.h>
#include <strings.h>
#include <string.h>
#include "libs/generator.h"
#include "libs/logger.h"
#include "libs/carlib.h"
#include "libs/arraylib.h"
#include "libs/quicksort.h"
#include "libs/shakersort.h"
#include "libs/selectionsort.h"


array readInput(char* filename) {
    FILE *fptr = fopen(filename, "r");
    if (fptr == NULL)
        logErrorAndExit("can not open file", 3);

    array cars = initArray();

    char* line = NULL;
    size_t len = 0;
    while ((getline(&line, &len, fptr)) != -1) {
        line[strcspn(line, "\n")] = 0;
        if (strcmp(line, "model,owner,mileage") == 0)
            continue;
        char* model = strtok(line, ",");
        char* owner = strtok(NULL, ",");
        float mileage = atof(strtok(NULL, ","));
        car c = createCar(model, owner, mileage);
        if (c.verified)
            append(&cars, c);
    }

    fclose(fptr);
    if (line) free(line);

    return cars;
}


void writeOutput(char* filename, array* cars) {
    FILE *fptr = fopen(filename, "w");
    if (fptr == NULL)
        logErrorAndExit("can not open file", 3);
    
    fprintf(fptr, "model,owner,mileage\n");
    for (int i = 0; i < cars->length; i++) {
        fprintf(
            fptr, 
            "%s,%s,%f\n", 
            cars->data[i].model, 
            cars->data[i].owner, 
            cars->data[i].mileage
        );
    }

    fclose(fptr);
}


int main(int argc, char *argv[]) {
    int ascendingOrder = 0;
    char sortingAlgo = '_';
    char sortingField = '_';
    char* inputFile = NULL;
    char* outputFile = NULL;

    int opt;
    while ((opt = getopt(argc, argv, ":s:f:ad")) != -1) {
        switch (opt) {
            case 'a':
                ascendingOrder = 1; break;
            case 'd':
                ascendingOrder = -1; break;
            case 's':
                if (strcmp(optarg, "quick") == 0) sortingAlgo = 'q';
                else if (strcmp(optarg, "shaker") == 0) sortingAlgo = 'h';
                else if (strcmp(optarg, "selection") == 0) sortingAlgo = 's';
                else logWarning("invalid sorting algorithm");
                break;
            case 'f':
                if (strcmp(optarg, "model") == 0) sortingField = 'm';
                else if (strcmp(optarg, "owner") == 0) sortingField = 'o';
                else if (strcmp(optarg, "mileage") == 0) sortingField = 'a';
                else logWarning("invalid sorting field");
                break;
            case ':':
                logWarning("option needs a value"); break;
            case '?':
                logWarning("unknown option"); break;
        }
    }

    for (; optind < argc; optind++) {
        if (inputFile == NULL)
            inputFile = argv[optind];
        else if (outputFile == NULL)
            outputFile = argv[optind];
        else {
            logWarning("extra arguments");
            break;
        }
    }

    if (ascendingOrder == 0) 
        logErrorAndExit("sorting order is not specified", 4);
    if (sortingAlgo == ' ') 
        logErrorAndExit("sorting algorithm is not specified", 4);
    if (sortingField == 0) 
        logErrorAndExit("sorting field is not specified", 4);
    if (inputFile == NULL)
        logErrorAndExit("input file is not specified", 4);
    if (outputFile == NULL)
        logErrorAndExit("output file is not specified", 4);

    array cars = readInput(inputFile);

    if (sortingAlgo == 'q')
        quickSortCars(&cars, ascendingOrder, sortingField);
    else if (sortingAlgo == 'h')
        shakerSortCars(&cars, ascendingOrder, sortingField);
    else
        selectionSortCars(&cars, ascendingOrder, sortingField);

    writeOutput(outputFile, &cars);

    arrayMemoryFree(&cars);

    return 0;
}
