#pragma once

#include <iostream>
#include <fstream>
#include "Date.h"
#include <string>
#include <Windows.h>
#include <algorithm>
#include "ListaCoches.h"
#include "Alquiler.h"
#include <vector>

using namespace std;

class ListaAlquileres
{
private:
	int numAlquileres;
	vector<Alquiler> alquileres;
	ListaCoches lC;

	void ordenaAlquileres() 
	{
		sort(alquileres.begin(), alquileres.begin() + numAlquileres);
	}

public:
	/*bool leerAlquileres()
	{
		ifstream entrada("rent.txt");

		if (entrada.is_open())
		{
			entrada >> numAlquileres;

			for (int i = 0; i < numAlquileres; i++) {
				Alquiler a;

				a.leeAlquiler(entrada);
				alquileres.push_back(a);

				int matID = lC.buscarCoche(a.devuelveMat());

				if (matID != -1)
				{
					alquileres[i].añadeCoche(lC.devuelveCoche(matID));
				}
				else 
				{
					alquileres[i].añadeCoche(nullptr);
				}

				
			}
			ordenaAlquileres();
			for (int i = 0; i < numAlquileres; i++) {
				alquileres[i].imprimeStats();
			}
		}

		return entrada.is_open();
	}*/
};

