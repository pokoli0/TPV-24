#pragma once

#include <iostream>
#include <fstream>
#include "Date.h"
#include <string>
#include <Windows.h>
#include <algorithm>
#include "Coche.h"
#include <vector>

using namespace std;

class ListaCoches
{
private:
	vector<Coche*> elems;
	size_t numElems;
	size_t capacidad;

public:
	/*bool leerModelos()
	{
		ifstream entrada("coches.txt");

		if (entrada.is_open())
		{
			entrada >> numCoches;

			for (int i = 0; i < numCoches; i++) {
				Coche c;
				c.leeCoche(entrada);
				coches.push_back(c);

				c.imprimeStats();
			}
		}

		return entrada.is_open();
	}

	int buscarCoche(const int codigo)
	{
		int i = 0;
		
		while (i < numCoches && codigo != coches[i].devuelveMat())
		{
			i++;
		}
		
		if (i == numCoches)
		{
			i = -1;
		}
		
		return i;
	}

	Coche* devuelveCoche(int pos) {
		return &coches[pos];
	}*/

	ListaCoches() {}
	~ListaCoches() {}

	int buscaCoche(int codigo) const {
		int i = 0;

		while (i < numElems && codigo != elems[i]->getCodigo())
		{
			i++;
		}

		if (i == numElems)
		{
			i = -1;
		}

		return i;
	}

	void insertaCoche(const Coche& c) {
		Coche* auxCoche = new Coche(c);
		elems.push_back(auxCoche);
	}

	friend ostream& operator<<(ostream& os, const ListaCoches& lc) {
		return os;
	}

	friend istream& operator>>(istream& is, ListaCoches& lc) {
		return is;
	}
};

