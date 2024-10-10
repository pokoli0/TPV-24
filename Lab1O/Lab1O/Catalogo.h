#pragma once
#include "Ejemplar.h"
using namespace std;
class Catalogo
{
public:
	Catalogo() {};
	Catalogo(istream& input);
	~Catalogo();

	bool LeeCatalogo(string fichero);

	// Devuelve ejemplar segun su codigo
	Ejemplar* buscaEjemplar(const int cod, int ini, int fin) const;
	void insertaEjemplar(char tipo , string Nombre);
	void mostrarCatalogo();
	friend void operator<<(ostream&, const Catalogo&);

private:
	Ejemplar* elems;
	size_t NumElems;
	size_t capacidad;
	Ejemplar** ejemplar;
};

