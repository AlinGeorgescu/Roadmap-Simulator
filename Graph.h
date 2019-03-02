/**
 * Copyright 2018
 * 
 * Fișier header cu definiția clasei graf.
 */

#ifndef GRAPH_H_
#define GRAPH_H_

// Biblioteci
#include <vector>

// Declarări using
using std::vector;

/**
 * Structura unui nod
 */
template <typename T>
struct Node {
    // Lista de vecini
    vector<int> neighbors;
    // Data generică reținută în nod
    T data;
    // Gradul interior al nodului
    int intern = 0;
};

/**
 * Graf orientat, implementat utilizând liste de adiacență.
 * 
 * Implementare generică.
 */
template <typename T>
class Graph {
 private:
    // Listele de vecini
    vector< Node<T> > nodes;
    // Numărul de noduri din graf
    int size = 0;
    // Iteratorul prin listele de vecini
    typename vector<int>::iterator it;

 public:
    // Numărul de componente conexe din graf
    int numConnectedComponents = 0;

    // Constructor
    Graph(int size, T data[]) {
        this->size = size;
        nodes.resize(size);
        for (int i = 0; i < size; ++i) {
            nodes[i].neighbors.resize(0);
            nodes[i].data = data[i];
        }
    }

    // Destructor
    ~Graph() {
    }

    /**
     * Adaugă o muchie între noduri.
     *
     * @param src - Nodul sursă al muchiei.
     * @param dst - Vârful muchiei.
     * 
     * Parametrii au aceeași semnificație și în funcțiile următoare.
     */
    void addEdge(int src, int dst) {
        nodes[src].neighbors.push_back(dst);
        ++nodes[dst].intern;
    }

    /**
     * Elimină o muchie din graf, dacă aceasta există.
     */
    void removeEdge(int src, int dst) {
        for (it = nodes[src].neighbors.begin();
             it != nodes[src].neighbors.end();
             /* Incrementare în for */) {
            if (*it == dst) {
                nodes[src].neighbors.erase(it);
            }
            else
                ++it;
        }

        --nodes[dst].intern;
    }

    /**
     * Verică dacă există o muchie între două noduri.
     * 
     * @returnează adevărat dacă exsistă o muchie de la src la dst,
     * fals în caz contrar.
     */
    bool hasEdge(int src, int dst) {
        for (it = nodes[src].neighbors.begin();
             it != nodes[src].neighbors.end();
             ++it) {
            if (*it == dst)
                return true;
        }

        return false;
    }

    /**
     * Întoarce lista de vecini a unui nod.
     *
     * @param node - Nodul ai cărui vecini vor fi returnați.
     * @returnează un vector ce conține vecinii.
     */
    vector<int> getNeighbors(int node) {
        return nodes[node].neighbors;
    }

    /**
     * Întoarce mărimea grafului, adică numărul de noduri din el.
     */
    int getSize() {
        return size;
    }

    /**
     * Întoarce gradul interior al unui nod, adică numărul de muchii
     * spre acesta.
     */
    int trafficIntensity(int node) {
        return nodes[node].intern;
    }

    /**
     * Funcție de schimbare a datelor dintr-un nod.
     */
    void changeData(int node, T data) {
        nodes[node].data = data;
    }
};

#endif  // GRAPH_H_
