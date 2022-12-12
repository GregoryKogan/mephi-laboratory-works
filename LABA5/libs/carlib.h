#ifndef CARS_H
#define CARS_H


typedef struct Car {
    char model[16 + 1];
    char* owner;
    float mileage;
    bool verified;
} car;
car createCar(char model[], const char* owner, float mileage);
void carMemoryFree(car c);
void printCar(car c);


#endif
