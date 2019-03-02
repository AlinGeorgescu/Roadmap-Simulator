/**
 * Copyright 2018 Alin-Andrei Georgescu (alinandrei2007@yahoo.com)
 * 312 CA
 * Tema 2 - Hit the Road
 * 
 * Fișier header cu definiția clasei tabelului de dispersie.
 */

#ifndef HASHTABLE_H_
#define HASHTABLE_H_

// Biblioteci
#include <iterator>
#include <vector>

// Declarări using
using std::vector;

// Structura unui element din tabel
template <typename Tkey, typename Tvalue>
struct elem_info {
	Tkey key;
	Tvalue value;
};

template <typename Tkey, typename Tvalue>
class Hashtable {
 private:
	// Pointer către grupări
	vector< struct elem_info<Tkey, Tvalue> > *H;
	// Numărul maxim de grupări
	int HMAX;
	// Pointer către funcția de hash
	unsigned int (*hash)(Tkey);
	// Numărul de elemente din tabelul de dispersie.
	unsigned int size;
	// Iteratorul prin liste
	typename vector< struct elem_info<Tkey, Tvalue> >::iterator it;

 public:
	// Constructor
	Hashtable(int HMAX, unsigned int (*hash)(Tkey)) {
		// Funcția de hash
		this->hash = hash;
		// Capacitatea maximă este HMAX bucketuri.
		this->HMAX = HMAX;
		// Se alocă bucketurile.
		this->H = new vector< struct elem_info<Tkey, Tvalue> > [HMAX];
		// Mărimea inițială este 0, niciun element nu este în tabel.
		this->size = 0;
	}

	// Destructor
	~Hashtable() {
		delete[] H;
	}

	/**
	 * Metoda de adăugare în tabel
	 */
	void put(Tkey key, Tvalue value) {
		/**
		 * Pentru fiecare element, pentru orice metodă legată de tabel, se va
		 * calcula indexul utilizând funcția de hash.
		 */
		int index = hash(key) % HMAX;

		/**
		 * În cazul în care cheia exsită deja în tabel, valoarea asociată
		 * acesteia este modificată.
		 */
		for (it = H[index].begin(); it != H[index].end(); ++it) {
			if (it->key == key) {
				it->value = value;
				return;
			}
		}

		// Dacă nu există deja în tabel, cheia este adăugată.
		struct elem_info<Tkey, Tvalue> info = {.key = key, .value = value};
		H[index].push_back(info);
		/**
		 * Se crește numărul de elemente din tabel doar dacă se adaugă o cheie
		 * nouă.
		 */
		++size;
	}

	/**
	 * Metoda de eliminare a unei chei din tabel.
	 */
	void remove(Tkey key) {
		int index = hash(key) % HMAX;

		// Se caută cheia și se șterge, alături de valoarea asociată.
		for (it = H[index].begin(); it != H[index].end(); ++it) {
			if (it->key == key) {
				it = H[index].erase(it);
				// Se scade numărul de elemente.
				--size;
			}
		}
	}

	/**
	 * Metoda de căutare a cheii în tabel
	 * 
	 * @retureneză valoarea asociată.
	 */
	Tvalue get(Tkey key) {
		int index = hash(key) % HMAX;

		// Dacă există în tabel cheia, se returnează valoarea asociată.
		for (it = H[index].begin(); it != H[index].end(); ++it) {
			if (it->key == key) {
				return it->value;
			}
		}
		return Tvalue();
	}

    /**
     * Verică dacă există cheia în tabel.
     * 
     * @returnează adevărat dacă exsistă, fals în caz contrar.
     */
	bool has_key(Tkey key) {
		int index = hash(key) % HMAX;

		for (it = H[index].begin(); it != H[index].end(); ++it) {
			if (it->key == key) {
				return true;
			}
		}

		return false;
	}

	/**
	 * Întoarce dimensiunea tabelului de dispersie.
	 */
	int get_size() {
		return size;
	}

	/**
	 * Întoarce capacitatea tabelului.
	 */
	int get_capacity() {
		return HMAX;
	}

	/**
	 * Întoarce factorul de dispersie al tabelului.
	 */
	float current_factor(){
		return (float)(size) / (float)(HMAX);
	}
};

#endif  // HASHTABLE_H_
