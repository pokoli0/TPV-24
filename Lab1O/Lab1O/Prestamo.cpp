#include "Prestamo.h"

Prestamo::Prestamo(Ejemplar* e, Date f, int user)
{
}

Prestamo::operator<(const Prestamo& otro) const
{
	return fecha < otro.fecha;
}
