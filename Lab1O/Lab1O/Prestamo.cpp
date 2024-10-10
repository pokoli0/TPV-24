#include "Prestamo.h"

Prestamo::Prestamo(Ejemplar* e, Date f, int user)
{
	ejemplar = e;
	fecha = f;
	usuario = user;
}

bool Prestamo::operator<(const Prestamo& otro) const
{
	return fecha < otro.fecha;
}

istream& operator>>(istream& in, Prestamo& p)
{
	// TODO
	return in;
}

ostream& operator<<(ostream& o, const Prestamo& p)
{
	return o; // esto esta mal, es pa q devuelva algo
}
