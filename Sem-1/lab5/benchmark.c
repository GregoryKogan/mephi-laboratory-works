#include "libs/arraylib.h"
#include "libs/generator.h"
#include "libs/logger.h"
#include "libs/quicksort.h"
#include "libs/selectionsort.h"
#include "libs/shakersort.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include <time.h>
#include <unistd.h>

clock_t runTests(int ascendingOrder, char sortingAlgo, char sortingField,
                 int numOfItems, int numOfArrays) {

  if (sortingAlgo == 'q')
    printf("Algorithm: Quick\n");
  else if (sortingAlgo == 'h')
    printf("Algorithm: Shaker\n");
  else
    printf("Algorithm: Selection\n");

  clock_t total_time = 0;
  for (int iter = 0; iter < numOfArrays; iter++) {
    array data = generateData((size_t)numOfItems);

    clock_t start, end;
    start = clock();
    if (sortingAlgo == 'q')
      quickSortCars(&data, ascendingOrder, sortingField);
    else if (sortingAlgo == 'h')
      shakerSortCars(&data, ascendingOrder, sortingField);
    else
      selectionSortCars(&data, ascendingOrder, sortingField);
    end = clock();

    arrayMemoryFree(&data);

    clock_t microseconds = (end - start) / (CLOCKS_PER_SEC / 1000000);
    total_time += microseconds;
    printf("Iter %d, time: %lu microseconds\n", iter, microseconds);
  }

  clock_t result = total_time / numOfArrays;
  printf("\x1b[32mAverage time: %lu microseconds\x1b[0m\n", result);
  return result;
}

int main(int argc, char *argv[]) {
  srand(time(NULL));

  int ascendingOrder = 0;
  char sortingAlgo = '_';
  char sortingField = '_';
  int numOfItems = -1;
  int numOfArrays = -1;

  int opt;
  while ((opt = getopt(argc, argv, ":s:f:ad")) != -1) {
    switch (opt) {
    case 'a':
      ascendingOrder = 1;
      break;
    case 'd':
      ascendingOrder = -1;
      break;
    case 's':
      if (strcmp(optarg, "quick") == 0)
        sortingAlgo = 'q';
      else if (strcmp(optarg, "shaker") == 0)
        sortingAlgo = 'h';
      else if (strcmp(optarg, "selection") == 0)
        sortingAlgo = 's';
      else
        logWarning("invalid sorting algorithm");
      break;
    case 'f':
      if (strcmp(optarg, "model") == 0)
        sortingField = 'm';
      else if (strcmp(optarg, "owner") == 0)
        sortingField = 'o';
      else if (strcmp(optarg, "mileage") == 0)
        sortingField = 'a';
      else
        logWarning("invalid sorting field");
      break;
    case ':':
      logWarning("option needs a value");
      break;
    case '?':
      logWarning("unknown option");
      break;
    }
  }

  for (; optind < argc; optind++) {
    if (numOfItems == -1)
      numOfItems = atoi(argv[optind]);
    else if (numOfArrays == -1)
      numOfArrays = atoi(argv[optind]);
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
  if (numOfItems == -1)
    logErrorAndExit("number of items is not specified", 4);
  if (numOfArrays == -1)
    logErrorAndExit("number of arrays is not specified", 4);

  runTests(ascendingOrder, sortingAlgo, sortingField, numOfItems, numOfArrays);

  return 0;
}
