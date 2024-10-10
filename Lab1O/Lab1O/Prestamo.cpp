#include "Prestamo.h"

Prestamo::Prestamo(Ejemplar* e, Date f, int user)
{
}

bool Prestamo::operator<(const Prestamo& otro) const
{
	return fecha < otro.fecha;
}

ostream& operator<<(ostream& o, const Prestamo& p)
{
	return o; // esto esta mal, es pa q devuelva algo
}
