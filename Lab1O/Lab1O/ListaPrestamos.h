#pragma once
#include "Prestamo.h"
#include "Catalogo.h"
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
	void ordena();
	void insertaPrestamo(const Prestamo&);
	friend void operator<<(ostream&, const ListaPrestamos&);
};

