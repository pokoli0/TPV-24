#pragma once
#include "Ejemplar.h"
class Catalogo
{
public:
	Catalogo(istream& input);
	~Catalogo();

	void buscaEjemplar(int n) const;

	void insertaEjemplar(Tipo tipo , string Nombre);

	friend void operator<<(ostream&, const Catalogo&);

private:
	Ejemplar* elems;
	size_t NumElems;
	size_t capacidad;

};

