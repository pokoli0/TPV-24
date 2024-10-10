#include "Ejemplar.h"

Ejemplar::Ejemplar(int cod, Tipo tipo, string nom)
{
	codigo = cod;
	tipo = tipo;
	nombre = nom;
}

ostream& operator<<(ostream& f, const Ejemplar& e)
{
	f << "Código: " << e.codigo << ", Tipo: " << e.tipo << ", Nombre: " << e.nombre;
	return f;
}

istream& operator>>(istream& f, Ejemplar& e)
{
	cout << "Introduce el código del ejemplar: ";
	f >> e.codigo;
	cout << "Introduce el tipo del ejemplar: ";
	f >> e.tipo;
	cout << "Introduce el nombre del ejemplar: ";
	f >> e.nombre;
	return f;
}
