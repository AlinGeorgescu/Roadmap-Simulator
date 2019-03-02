/**
 * Copyright 2018 Alin-Andrei Georgescu (alinandrei2007@yahoo.com)
 * 312 CA
 * Tema 2 - Hit the Road
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
