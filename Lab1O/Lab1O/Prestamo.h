#pragma once

#include "Ejemplar.h"
#include "Date.hpp"

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

private:
	Date fecha;
	int usuario;
	Ejemplar* ejemplar;
};

