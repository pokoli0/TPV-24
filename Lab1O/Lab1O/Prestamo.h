#pragma once

#include "Ejemplar.h"
#include "Date.hpp"
#include <iostream>

using namespace std;

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

	//operadores
	friend istream& operator>>(istream& in, Prestamo& p);
	friend ostream& operator<<(ostream& out, const Prestamo& p);

private:
	Date fecha;
	int usuario;
	Ejemplar* ejemplar;
};

