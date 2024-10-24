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
		tamArray = n;
		arrayCatalogo = new Ejemplar[n];

		for (int i = 0; i < n; i++)
		{
			//arrayCatalogo[i] = new Ejemplar;
			input >> codigo;
			arrayCatalogo[i].setCodigo(codigo);
			input >> tipo;
			arrayCatalogo[i].setTipo(tipo);
			getline(input, titulo);
			arrayCatalogo[i].setNombre(titulo);
		}
	}

	input.close();

	return encontrado;
}
Ejemplar* Catalogo::buscaEjemplar(const int cod, int ini, int fin) const
{
	int elems = fin - ini;

	if (elems == 0) return nullptr;
	if (elems == 1) return getEjemplar(ini);

	int mitad = (ini + fin) / 2;

	if (cod >= getEjemplar(mitad)->getCodigo())
	{
		return buscaEjemplar(cod, mitad, fin);
	}
	if (cod < getEjemplar(mitad)->getCodigo())
	{
		return buscaEjemplar(cod, ini, mitad);
	}

	cout << "Catalogo::buscaEjemplar(): No se encuentra ejemplar." << endl;
	return nullptr;
}
void Catalogo::mostrarCatalogo() {
	if (tamArray == 0) {
		cout << "No hay coches disponibles en la lista." << endl;
	}

	cout << "Lista de Libros, juegos y audiolibros:" << endl;
	cout << "-------------------------------------------------------" << endl;
	for (int i = 0; i < tamArray; i++) {
		cout << "Codigo: " << getEjemplar(i)->getCodigo() << endl
			<< "Tipo: " << getEjemplar(i)->mostrarTipo() << endl
			<< "Nombre:" << getEjemplar(i)->getNombre() << endl
		//dejar espacio entre libros etc
		<< "-------------------------------------------------------" << endl;
	}


}
void Catalogo::insertaEjemplar(char tipo, string nombre)
{
	if (contC < maxTam)
	{
		int codigo = arrayCatalogo[tamArray - 1].getCodigo() + 1;

		int tamAux = tamArray + 1;
		Ejemplar* aux = new Ejemplar[tamAux];

		copy(arrayCatalogo, arrayCatalogo + 1, aux);

		delete[] arrayCatalogo;

		arrayCatalogo = aux;
		tamArray = tamAux;

		arrayCatalogo[tamArray - 1].setCodigo(codigo);

		switch (tipo) {
		case 'L':
			arrayCatalogo[tamArray - 1].setTipo(0);
			break;

		case 'A':
			arrayCatalogo[tamArray - 1].setTipo(1);
			break;

		default:
			arrayCatalogo[tamArray - 1].setTipo(2);
			break;
		}

		arrayCatalogo[tamArray - 1].setNombre(nombre);

		contC++;

		ofstream catalogoWrite("catalogo.txt", std::ios::app);
		catalogoWrite << codigo << " " << tipo << " " << arrayCatalogo[tamArray - 1].getNombre() << endl;

		catalogoWrite.close();
	}
}

void operator<<(ostream&, const Catalogo&)
{
}
