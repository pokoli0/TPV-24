#pragma once

#include "Ejemplar.h"
#include "Date.hpp"
#include <iostream>

class Prestamo
{
public:
	Prestamo() {};
	Prestamo(Ejemplar* e, Date f, int user);

	Ejemplar* getEjemplar() {
		return ejemplar;
	}

	Date getFecha() {
		return fecha;
	}

	int getUsuario() const {
		return usuario;
	}

	void getDevolucion() const;


	bool operator<(const Prestamo&) const;
	//leePrestamo(istream&, const Catalogo&);
	//friend Prestamo& operator<<(ostream&, const Prestamo&);
private:
	Date fecha;
	int usuario;
	Ejemplar* ejemplar;
};

