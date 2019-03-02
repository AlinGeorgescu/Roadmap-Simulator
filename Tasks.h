/**
 * Copyright 2018
 * 
 * Fișier header cu definițiile funcțiilor ce rezolvă tema.
 */

#ifndef TASKS_H_
#define TASKS_H_

// Biblioteci
#include <string>
#include <fstream>
#include <vector>
#include <queue>
#include <stack>
#include <algorithm>
#include <iterator>

// Fișiere
#include "Structs.h"

// Declarări using
using std::string;
using std::ofstream;
using std::vector;
using std::queue;
using std::stack;

/**
 * Se afișează orașul (nodul din graf) cu gradul interior maxim, adică orașul
 * ce este destinația celor mai multe muchii.
 */
void task1(Graph<int> *map, Hashtable<int, string> *decode) {
    ofstream fout("task1.out");
    int size = map->getSize();
    int max = 0;
    int traffic;
    string city;

    /**
     * Gradul interior este calculat pentru fiecare nod la citirea grafului,
     * iar funcția curentă doar calculează maximul.
     */
    for (int i = 0; i < size; ++i) {
        traffic = map->trafficIntensity(i);
        if (traffic > max) {
            max = traffic;
            city = decode->get(i);
        }
    }

    fout << city << " " << max << '\n';

    fout.close();
}

/**
 * Funcția recursivă de parcurgere în adâncime a unui graf.
 */
static void rDFS(Graph<int> *graph, bool visited[], int node) {
    visited[node] = true;
    vector<int> v = graph->getNeighbors(node);

    for (unsigned int i = 0; i < v.size(); ++i){
        if (visited[v[i]] == false)
            rDFS(graph, visited, v[i]);
    }
}

/**
 * Funcția ce determină numărul de componente conexe din graf, utilizând
 * parcurgerea în adâncime.
 */
void connectedComponents(Graph<int> *graph) {
    int numNodes = graph->getSize();
    bool visited[numNodes] = {false};

    for (int i = 0; i < numNodes; ++i) {
        if (visited[i] == false) {
            rDFS(graph, visited, i);
            ++graph->numConnectedComponents;
        }
    }
}

/**
 * Se verifică dacă harta este validă, adică dacă toate nodurile aparțin unei
 * singure componente tare conexe.
 */
void task2(Graph<int> *map, Graph<int> *transpose) {
    ofstream fout("task2.out");

    connectedComponents(map);
    connectedComponents(transpose);

    /**
     * Verific dacă există o singură componentă pe graful hartă, dar și pe
     * transpusul acestuia.
     */
    if (map->numConnectedComponents == 1 &&
        transpose->numConnectedComponents == 1)
        fout << "HARTA VALIDA\n";
    else
        fout << "HARTA INVALIDA\n";

    fout.close();
}

/**
 * Calculez componentele tare conexe din care fac parte nodurile date și afișez
 * orașele din toate celelalte mulțimi disjuncte cu cele aflate. 
 */
void task3(int N, int K, int index,
           string isolated,
           Graph<int> *map,
           Graph<int> *transpose,
           Hashtable<int, string> *decode,
           ofstream &fout) {
    bool visited[N] =  {false};
    bool visited_transpose[N] = {false};

    /**
     * Determin componentele tare conexe prin aplicarea a 2 DFS-uri, unul pe
     * graf și unul pe transpusul acestuia.
     */
    rDFS(map, visited, index);
    rDFS(transpose, visited_transpose, index);

    fout << "Orase inaccesibile pentru " << isolated << ": ";

    /**
     * Toate orașele nevizitate printr-una dintre metode sunt inaccesibile din
     * orașul curent.
     */
    for (int j = 0; j < N; ++j) {
        if (visited[j] == false || visited_transpose[j] == false) {
            fout << decode->get(j) << ' ';
        }
    }

    fout << '\n';
}

/**
 * Un algoritm de parcurgere în lățime adaptat, pentru aflarea distanței
 * celui mai scurt drum dintre un nod din graf și o colecție de posibile
 * destinații.
 * 
 * @returnează distanța minimă.
 */
int minPath(int N, int B, Graph<int> *map, int source, int *gas) {
	bool visited[N] = {false};
	queue<int> Q;
	int d[N] = {9999999};

    d[source] = 0;
    Q.push(source);
    while (!Q.empty()) {
        int v = Q.front();
        Q.pop();
        vector<int> n = map->getNeighbors(v);
        for (auto u = n.begin(); u != n.end(); ++u) {
            if (visited[*u] == false) {
                visited[*u] = true;
                d[*u] = d[v] + 1;
                Q.push(*u);

                for (int i = 0; i < B; ++i) {
                    if (gas[*u] == 1 && *u != source)
                        return d[*u];
                }
            }
        }
    }

	return 9999999;
}

/**
 * Calculez distanța minimă dintre fiecare nod citit și o benzinărie și aflu
 * dacă o mașina poate ajunge acolo, dați fiind niște parametrii ai săi:
 *          - combustibil în rezervor
 *          - consum de carburant
 */
void task4(int N, int L, int B,
           int *gas,
           struct Car journey,
           Graph<int> *map,
           Hashtable<string, int> *encode,
           ofstream &fout) {
    int source, dist;

    if (journey.consumption > journey.fuel) {
        fout << "NU\n";
    } else {
        source = encode->get(journey.cityName);
        dist = minPath(N, B, map, source, gas);

        if (dist * journey.consumption <= journey.fuel)
            fout << "DA "
                 << journey.fuel - dist * journey.consumption
                 << '\n';
        else
            fout << "NU\n";
    }
}

/**
 * Un algoritm de parcurgere în lățime adaptat, pentru aflarea drumului
 * cel mai scurt dintre 2 noduri din graf.
 * 
 * @returnează nodurile parcurse sub forma unei stive, cu vărful fiind
 * destinația, iar baza sursa traseului.
 */
stack<int> showMinPath(int source, int dest, Graph<int> *map) {
	typename vector<int>::iterator u;
    int numNodes = map->getSize();
    bool visited[numNodes] = {false};
    // Vectorul de părinți
    int p[numNodes] = {-1};
	queue<int> Q;

    Q.push(source);
    while (!Q.empty()) {
        int v = Q.front();
        if (v == dest)
            break;
        Q.pop();
        vector<int> n = map->getNeighbors(v);
        sort(n.begin(), n.end());
        for (u = n.begin(); u != n.end(); ++u) {
            if (!visited[*u]) {
                visited[*u] = true;
                p[*u] = v;
                Q.push(*u);
            }
            if (*u == dest)
                break;
        }
    }

    // Stiva cale parcursă
	stack<int> path;
	// Dacă nu există drum spre destinație
	if (p[dest] == -1) return path;

	/**
     * Începe de la destinație, nodul curent devine părintele său și este
     * adăugat în stivă până când sursa este găsită.
     */
	while (dest != source) {
	 	path.push(dest);
	 	dest = p[dest];
	}
	path.push(source);

	return path;
}

/**
 * Afișează traseul frecventat de cei mai mulți călători, prin aplicarea unui
 * BFS ce returnează traseul parcurs între sursă și destinație.
 */
void task5(int src, int dst, int passangers,
           Graph<int> *map,
           Hashtable<int, string> *decode) {
        ofstream fout("task5.out");
        stack<int> S = showMinPath(src, dst, map);

        fout << passangers;
        while (!S.empty()) {
            fout  << ' ' << decode->get(S.top());
            S.pop();
        }
        fout << '\n';

        fout.close();
    }

/**
 * Fucția de comparare a unei rute prin orașul sursă și mai apoi prin orașul
 * destinație, utilizată în std::sort.
 */
bool sortFunc(const struct Route &a, const struct Route &b) {
    if (a.src > b.src)
        return false;

    if (a.src == b.src && a.dst > b.dst)
        return false;

    return true;
}

/**
 * Fucția de comparare a unei rute prin numărul de pasageri utilizată în
 * std::max_element (elementul maxim dintr-un vector).
 */
bool maxim(const struct Route &a, const struct Route &b) {
    return a.passangers < b.passangers;
}

#endif  // TASKS_H_
