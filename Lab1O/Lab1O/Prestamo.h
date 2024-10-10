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

	Ejemplar* getEjemplar() { return ejemplar;}
	void setEjemplar(Ejemplar* e) {	ejemplar = e;}

	Date getFecha() { return fecha;}
	void setFecha(Date date) { fecha = date; }

	Date getFechaDevolucion() { return fecha + (*this->ejemplar).getDiasDevolucion(); }

	int getUsuario() const {return usuario;}
	void setUsuario(int user) { usuario = user; }


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

