#pragma once
#include "Prestamo.h"
#include "Catalogo.h"
#include "Date.hpp"
#include <string>
#include <fstream>
#include <iostream>
#include <algorithm>
#include <Windows.h>

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
	//ordena lista segun fecha de devolucion
	void ordenarLista();
	void mostrarPrestamos();

	void ordena();
	void insertaPrestamo(const Prestamo&);
	friend void operator<<(ostream&, const ListaPrestamos&);
};

