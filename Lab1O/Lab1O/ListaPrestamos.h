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
	size_t Capacidad;
public:
	ListaPrestamos(){};
	ListaPrestamos(istream&, const Catalogo&);
	~ListaPrestamos();
	bool leerPrestamos(string fichero);
	void ordena();
	void insertaPrestamo(const Prestamo&);
	friend void operator<<(ostream&, const ListaPrestamos&);
};

