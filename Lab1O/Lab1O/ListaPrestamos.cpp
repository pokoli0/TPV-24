#include "ListaPrestamos.h"

ListaPrestamos::ListaPrestamos(istream&, const Catalogo&)
{
}

ListaPrestamos::~ListaPrestamos()
{
}

bool ListaPrestamos::leerPrestamos(string fichero, Catalogo& catalogo)
{
	bool encontrado;
	ifstream input;
	input.open(fichero);

	if (!input.is_open())
	{
		encontrado = false;
		cout << "no se encuentra el fichero :(" << endl;
	}
	else {
		encontrado = true;

		int n, codigo, user;
		Date fecha;

		input >> n; // 7
		arrayPrestamo = new Prestamo[maxArrayP];

		for (int i = 0; i < n; i++)
		{
			input >> codigo;
			input >> fecha;
			input >> user;

			arrayPrestamo[i].setEjemplar(catalogo.buscaEjemplar(codigo, 0, catalogo.getCapacidad()));
			arrayPrestamo[i].setFecha(fecha);
			arrayPrestamo[i].setUsuario(user);

			contP++;
		}
	}

	input.close();

	return encontrado;
}

void ListaPrestamos::ordenarLista()
{
	Prestamo* a = arrayPrestamo + contP;
	sort(arrayPrestamo, a);
}

void ListaPrestamos::mostrarPrestamos()
{
	Date* actual = new Date();
	for (int i = 0; i < contP; i++) {
		cout << arrayPrestamo[i].getFecha() <<
			" (en " <<
			arrayPrestamo[i].getFecha().diff(*actual) <<
			" dias) ";
			//arrayPrestamo[i].getEjemplar()->getNombre();

		if (arrayPrestamo[i].getFecha().diff(*actual) < 0) {
			cout << " (" <<
			arrayPrestamo[i].getFecha().diff(arrayPrestamo[i].getFechaDevolucion()) <<
			" dias de penalizacion)";
		}

			cout << endl;
	}
}

void ListaPrestamos::ordena()
{
}

void ListaPrestamos::insertaPrestamo(const Prestamo&)
{
}

void operator<<(ostream&, const ListaPrestamos&)
{
}
