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
	bool encontrado;
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
		char tipo;
		string titulo;
		input >> n;
		NumElems = n;
		ejemplar = new Ejemplar*[n];
		for (int i = 0; !input.eof() && i < n; i++)
		{
			ejemplar[i] = new Ejemplar;
			input >> codigo;
			ejemplar[i]->setCodigo(codigo);
			input >> tipo;
			ejemplar[i]->setTipo(tipo);
			input >> titulo;
			ejemplar[i]->setNombre(titulo);
		}
	}

	input.close();

	return encontrado;
}
Ejemplar* Catalogo::buscaEjemplar(const int cod, int ini, int fin) const
{
	int elems = fin - ini;

	if (elems == 0) return nullptr;
	if (elems == 1) return ejemplar[ini];

	int mitad = (ini + fin) / 2;

	if (cod >= ejemplar[mitad]->getCodigo())
	{
		return buscaEjemplar(cod, mitad, fin);
	}
	if (cod < ejemplar[mitad]->getCodigo())
	{
		return buscaEjemplar(cod, ini, mitad);
	}

	cout << "Catalogo::buscaEjemplar(): No se encuentra ejemplar." << endl;
	return nullptr;
}

void Catalogo::insertaEjemplar(char tipo, string Nombre)
{
}

void operator<<(ostream&, const Catalogo&)
{
}
