/**
 * Copyright 2018
 * 
 * Fișier header cu definiția structurilor City și Car.
 */

#ifndef STRUCTS_H_
#define STRUCTS_H_

// Biblioteci
#include <string>

// Declarări using
using std::string;

// Task 4
struct Car {
    string cityName;
    int fuel, consumption;
};

// Task 5
struct Route {
    string src, dst;
    int passangers;
};

#endif  // STRUCTS_H_
