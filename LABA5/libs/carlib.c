#include <stdio.h>
#include <strings.h>
#include <stdbool.h>
#include <stdlib.h>
#include "logger.h"


typedef struct Car {
    char model[16 + 1];
    char* owner;
    float mileage;
    bool verified;
} car;


bool verifyModel(char model[]) {
    if (strlen(model) > 16)
        return false;

    for (size_t i = 0; i < strlen(model); ++i) {
        if (
            (model[i] - 'A' < 0 || model[i] - 'A' > 'Z' - 'A')
            && (model[i] - 'a' < 0 || model[i] - 'a' > 'z' - 'a')
            && model[i] != ' ' 
            && model[i] != '-'
        ) return false;
    }
    return true;
}

bool verifyMileage(float m) {
    return (m >= 0);
}

car createCar(char model[], const char* owner, float mileage) {
    bool verified = true;

    if (!verifyModel(model)) {
        logError(
            "car model must be a string up to 16 characters long,"
            " which can only include letters, hyphens and spaces"
        );
        verified = false;
    }

    if (!verifyMileage(mileage)) {
        logError("car mileage must be at least zero");
        verified = false;
    }

    car c;
    strcpy(c.model, model);
    c.owner = strdup(owner);
    c.mileage = mileage;
    c.verified = verified;
    return c;
}

void carMemoryFree(car c) {
    free(c.owner);
    c.owner = NULL;
    c.mileage = 0;
    c.verified = false;
}

void printCar(car c) {
    printf(
        "Car<model: %s, owner: %s, mileage: %f>", 
        c.model, c.owner, c.mileage
    );
}
