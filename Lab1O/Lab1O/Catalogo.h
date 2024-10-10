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
	int buscaEjemplar(int n) const;
	void insertaEjemplar(char tipo , string Nombre);

	friend void operator<<(ostream&, const Catalogo&);

private:
	Ejemplar* elems;
	size_t NumElems;
	size_t capacidad;
	Ejemplar** ejemplar;
};

