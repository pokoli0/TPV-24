#include "Catalogo.h"
#include <fstream>
#include <iostream>
#include "Ejemplar.h"
Catalogo::Catalogo(istream& input)
{
}


Catalogo::~Catalogo()
{
}
bool Catalogo::LeeCatalogo(string fichero)
{
	bool encontrado = false;
	ifstream input;
	input.open(fichero);
	if (!input.is_open())
	{
		encontrado = false;
		cout << "no se encuentra el fichero :(" << endl;
	}
	else {
		encontrado = true;
		int n, codigo;
		input >> n;
		ejemplar = new Ejemplar*[n];
		for (int i = 0; !input.eof() && i < n; i++)
		{
			ejemplar[i] = new Ejemplar;
			input >> *ejemplar[i];
		}
	}

	return encontrado;
}
void Catalogo::buscaEjemplar(int n) const
{
}

void Catalogo::insertaEjemplar(char tipo, string Nombre)
{
}

void operator<<(ostream&, const Catalogo&)
{
}
