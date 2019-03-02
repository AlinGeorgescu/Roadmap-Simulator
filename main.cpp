/**
 * Copyright 2018 Alin-Andrei Georgescu (alinandrei2007@yahoo.com)
 * 312 CA
 * Tema 2 - Hit the Road
 * 
 * Fișierul principal
 */

// Biblioteci
#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <iterator>
#include <algorithm>

// Fișiere header cu definițiile claselor și codul funcțiilor
#include "Graph.h"
#include "Hashtable.h"
#include "Hash_functions.h"
#include "Structs.h"
#include "Tasks.h"

// Declarări using
using std::cin;
using std::string;
using std::ofstream;
using std::vector;
using std::sort;
using std::max_element;

int main() {
    // Variabile cu semnificațiile date în enunț
    int N, M, B, K, L, P;
    // Iterator, indecși orașe
    int i, indexSRC, indexDST;
    // Structura unei linii citite pentru taskul 4
    struct Car journey;
    // Nume de orașe
    string name, src, dst;
    // Nume orașe pentru taskul 3
    string isolated;
    // Nume orașe cu benzinării pentru taskul 4
    string station;
    // Iterator prin vectorul de la taskul 5
    typename vector<struct Route>::iterator it;

    cin >> N >> M;

    // Cele 2 tabele de dispersie
    Hashtable<string, int> encode(N, &charHashingFunction);
    Hashtable<int, string> decode(N, &hashingFunction);
    // Parametru pentru constructorul grafului, adaugă date în fiecare nod.
    int nodes[N];
    // Vectorul de marcare a benzinăriilor pentru taskul 4
    int gas[N] = {0};

    /**
     * Citire nodurilor din graf (numele orașelor) și indexarea lor în tabelele
     * de dispersie.
     */
    for (i = 0; i < N; ++i) {
        cin >> name;
        encode.put(name, i);
        decode.put(i, name);
        nodes[i] = i;
    }

    // Graful hartă
    Graph<int> map(N, nodes);
    // Graful transpus
    Graph<int> transpose(N, nodes);

    // Citirea muchiilor din graf (autostrăzile)
    for (i = 0; i < M; ++i) {
        cin >> src >> dst;
        indexSRC = encode.get(src);
        indexDST = encode.get(dst);
        map.addEdge(indexSRC, indexDST);
        transpose.addEdge(indexDST, indexSRC);
    }

    // Rezolvare Task 1
    task1(&map, &decode);
    // Rezolvare Task 2
    task2(&map, &transpose);

    // Citirea orașelor cu benzinării și marcarea lor în vectorul gas.
    cin >> B;
    for (i =0; i < B; ++i) {
        cin >> station;
        gas[encode.get(station)] = 1;
    }

    // Rezolvare Task 3
    ofstream fout("task3.out");
    cin >> K;
    /**
     * Dacă harta este validă citesc cele K orașe doar pentru a muta cursorul
     * în fișier.
     */
    if (map.numConnectedComponents == 1 &&
       transpose.numConnectedComponents == 1) {
        fout << "Exista drum intre oricare doua orase\n";
        for (i = 0; i < K; ++i) {
            cin >> isolated;
        }
    /**
     * Altfel, citesc cele K orașe, le caut indexul întreg în tabelul de
     * dispersie și apelez funcția de rezolvare.
     */
    } else {
       for (i = 0; i < K; ++i) {
           cin >> isolated;
           int index = encode.get(isolated);
           task3(N, K, index, isolated, &map, &transpose, &decode, fout);
        }
    }
    fout.close();

    // Rezolvare Task 4
    cin >> L;
    ofstream out("task4.out");
    for (i = 0; i < L; ++i) {
        cin >> journey.cityName
            >> journey.fuel
            >> journey.consumption;
        task4(N, L, B, gas, journey, &map, &encode, out);
    }
    out.close();

    // Rezolvare Task 5
    cin >> P;
    vector<struct Route> route(P);
    // Citesc cele P orașe și le sortez după orașul sursă și orașul destinație.
    for (i = 0; i < P; ++i) {
        cin >> route[i].src >> route[i].dst >> route[i].passangers;
    }
    sort(route.begin(), route.end(), sortFunc);

    /**
     * Fiind soartat, dacă exită 2 autobuze între aceleași 2 orașe, acestea vor
     * poziționate unul lângă altul în vector. Adun numărul de pasageri pentru
     * acestea.
     */

    for (i = 0; i < P - 1; ++i) {
        if (route[i].src == route[i + 1].src &&
            route[i].dst == route[i + 1].dst) {
            route[i].passangers += route[i + 1].passangers;
            route[i + 1].passangers = route[i].passangers;
        }
    }
    // Calculez numărul maxim de pasageri și afișez traseul pentru acele curse.
    it = max_element(route.begin(), route.end(), maxim);
    task5(encode.get(it->src),
          encode.get(it->dst),
          it->passangers,
          &map, &decode);

    return 0;
}
