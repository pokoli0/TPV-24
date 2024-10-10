#pragma once
#include "Prestamo.h"
#include "Catalogo.h"
#include "Date.hpp"
#include <fstream>
#include <iostream>

class ListaPrestamos
{
private:
	Prestamo* elems;
	size_t numElems;
	size_t capacidad; // igual no hace falta

public:
	ListaPrestamos() {};
	ListaPrestamos(istream& const e, const Catalogo& c);
	~ListaPrestamos();

	bool leerPrestamos(string fichero, Catalogo& catalogo);
	void mostrarPrestamos();

	void ordena();
	void insertaPrestamo(const Prestamo&);
	friend void operator<<(ostream&, const ListaPrestamos&);
};

