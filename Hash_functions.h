/**
 * Copyright 2018
 * 
 * Fișier header cu definițiile funcțiilor de hash.
 */

#ifndef HASH_FUNCTIONS_H_
#define HASH_FUNCTIONS_H_

// Macrodefiniții
#define int_hash  48251
#define string_hash 25000

// Biblioteci
#include <string>

// Declarări using
using std::string;

// Funcție de hash pentru numerele întregi.
unsigned int hashingFunction(int x) {
    return x % int_hash;
}

// Funcție de hash pentru șirurile de caractere.
unsigned int charHashingFunction(string str) {
    unsigned int h = 0;
    int i, size = str.length();
    int a = 1;

    for (i = 0; i < size; ++i) {
        h += str[size - i - 1] * a % string_hash;
        a *= 31;
    }

    return h;
}

#endif  // HASH_FUNCTIONS_H_
